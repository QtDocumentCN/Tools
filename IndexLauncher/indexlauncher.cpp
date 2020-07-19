#include "indexlauncher.h"

#include <atomic>
#include <chrono>
#include <vector>

#include <QtCore/QAbstractTableModel>
#include <QtCore/QBitArray>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QElapsedTimer>
#include <QtCore/QFile>
#include <QtCore/QRegularExpression>
#include <QtCore/QVector>
#include <QtGui/QClipboard>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include <QtGui/QKeyEvent>
#include <QtGui/QWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QVBoxLayout>

#include "threadpool.h"

using namespace std::literals::chrono_literals;

static const QString kStyleSheets = QStringLiteral("border: none;");
static constexpr int kMinWidth = 500;
static constexpr double kOpacity = 0.8;

static constexpr auto kFrameInterval = 10ms;

// [\*\=\"\\\'\/]
static const auto kSyntaxRegexp = [] {
  auto regexp = QRegularExpression{QStringLiteral("[\\*\\=\\\"\\\\\\'\\/]")};
  regexp.optimize();
  return regexp;
}();

// \[(\S+)\]\(\S+\)
static const auto kLinkRegexp = [] {
  auto regexp = QRegularExpression{QStringLiteral("\\[(\\S+)\\]\\(\\S+\\)")};
  regexp.optimize();
  return regexp;
}();

//[\w_]+::([\w_]+)\(
static const auto kMethodRegexp = [] {
  auto regexp = QRegularExpression{QStringLiteral("[\\w_]+::([\\w_]+)\\(")};
  regexp.optimize();
  return regexp;
}();

// [\w_]+::([\w_]+)
static const auto kMemberRegexp = [] {
  auto regexp = QRegularExpression{QStringLiteral("[\\w_]+::([\\w_]+)")};
  regexp.optimize();
  return regexp;
}();

// [\_\,\.\:\(\)\[\]\{\}]
static const auto kPunctuationRegexp = [] {
  auto regexp =
      QRegularExpression{QStringLiteral("[\\_\\,\\.\\:\\(\\)\\[\\]\\{\\}]")};
  regexp.optimize();
  return regexp;
}();

class Model : public QAbstractListModel {
  friend class IndexLauncher;

 public:
  explicit Model(QObject* parent = nullptr);

  void SelectFile(const QString& file = {});
  void Select(const QModelIndex& idx);
  void CopyCurrent();

  int rowCount(const QModelIndex& parent) const override;
  QVariant data(const QModelIndex& index, int role) const override;

 private:
  QString file_;

  // <File, <Title, (Text, Link)>>
  QMap<QString, QMultiMap<QString, QPair<QString, QString>>> titles_;
  QMultiMap<QString, QPair<QString, QString>>* currentData_ = nullptr;
  QModelIndex currentIndex_;
};

Model::Model(QObject* parent) : QAbstractListModel(parent) {}

void Model::SelectFile(const QString& file) {
  if (file != file_) {
    beginResetModel();
    file_ = file;
    currentData_ = file_.isEmpty() ? nullptr : &titles_[file_];
    endResetModel();
  }
}

void Model::Select(const QModelIndex& idx) {
  auto prev = index(currentIndex_.row(), currentIndex_.column());
  currentIndex_ = index(idx.row(), idx.column());
  emit dataChanged(prev, prev);
  emit dataChanged(currentIndex_, currentIndex_);

  auto list = qobject_cast<QListView*>(parent());
  auto filter = qobject_cast<QSortFilterProxyModel*>(list->model());
  list->scrollTo(filter->mapFromSource(currentIndex_));
}

void Model::CopyCurrent() {
  QChar ch = file_.front();
  if ((file_.length() > 1) && (ch == QLatin1Char('Q')) &&
      (file_.at(1).isUpper())) {
    ch = file_.at(1);
  }
  QString text =
      QStringLiteral("../../%1/%2/%2.md#%3")
          .arg(ch.toUpper())
          .arg(file_)
          .arg((currentData_->cbegin() + currentIndex_.row()).value().second);
  QGuiApplication::clipboard()->setText(text);
}

int Model::rowCount(const QModelIndex&) const {
  return file_.isEmpty() ? titles_.count() : titles_.value(file_).count();
}

QVariant Model::data(const QModelIndex& index, int role) const {
  switch (role) {
    case Qt::DisplayRole:
      if (currentData_) {
        auto it = currentData_->cbegin() + index.row();
        return QStringLiteral("%1\n%2").arg(it.key()).arg(it.value().first);
      } else {
        return (titles_.cbegin() + index.row()).key();
      }

    case Qt::BackgroundRole:
      if (index.row() == currentIndex_.row()) {
        return QColor(QStringLiteral("royalblue"));
      }
      break;

    default:
      break;
  }
  return {};
}

IndexLauncher::IndexLauncher(QWidget* parent, Qt::WindowFlags flags)
    : QFrame(parent, flags),
      input_(new QLineEdit(this)),
      list_(new QListView(this)),
      model_(new Model(list_)),
      filter_(new QSortFilterProxyModel(list_)) {
  auto layout = new QVBoxLayout(this);

  input_->setStyleSheet(kStyleSheets);
  input_->installEventFilter(this);
  layout->addWidget(input_);

  auto line = new QFrame(this);
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  layout->addWidget(line);

  filter_->setSourceModel(model_);
  filter_->setFilterCaseSensitivity(Qt::CaseInsensitive);
  list_->setModel(filter_);
  list_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  list_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  list_->setStyleSheet(kStyleSheets);
  list_->setSelectionMode(QAbstractItemView::NoSelection);
  layout->addWidget(list_);

  connect(input_, &QLineEdit::textChanged, [this](const QString& text) {
    filter_->setFilterFixedString(text);
    model_->Select(filter_->mapToSource(filter_->index(0, 0)));
  });
}

size_t IndexLauncher::IndexFiles(const QFileInfoList& files) {
  model_->beginResetModel();
  model_->titles_.clear();

  std::vector<std::future<void>> futures;
  std::atomic<size_t> count = ATOMIC_VAR_INIT(0);

  QProgressBar progress;
  progress.setTextVisible(false);
  progress.setMaximum(files.count() - 1);
  progress.setWindowFlags(Qt::Tool | Qt::FramelessWindowHint |
                          Qt::WindowStaysOnTopHint);
  progress.show();

  std::function<void(const QFileInfo&,
                     QMultiMap<QString, QPair<QString, QString>>*)>
      IndexFile;
  IndexFile = [&count](const QFileInfo& fileInfo,
                       QMultiMap<QString, QPair<QString, QString>>* titleMap) {
    QFile file{fileInfo.absoluteFilePath()};
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
      return;
    }

    while (!file.atEnd()) {
      QString line = file.readLine();
      if (!line.startsWith(QLatin1Char('#'))) {
        continue;
      }

      // Trim
      while (line.startsWith(QLatin1Char('#'))) {
        line.remove(0, 1);
      }
      line = line.trimmed();
      QString raw = line;

      // Remove syntax and strings * = " \ ' /
      line.replace(kSyntaxRegexp, QString{});

      // Replace markdown link [xxx](yyy) to xxx
      line.replace(kLinkRegexp, QStringLiteral("\\1"));
      QString unref = line;

      // Find function name
      QStringList titles;
      QRegularExpressionMatch match = kMethodRegexp.match(line);
      if (match.hasMatch()) {
        titles << match.captured(1);
      }

      // No function name, find other symbols
      if (titles.isEmpty()) {
        QRegularExpressionMatchIterator it = kMemberRegexp.globalMatch(line);
        while (it.hasNext()) {
          titles << it.next().captured(1);
        };
      }

      // Generate html link _ , . : ( ) [ ] { }
      line.replace(kPunctuationRegexp, QString{});
      line.replace(QLatin1Char('\t'), QLatin1Char('-'));
      if (titles.isEmpty()) {
        titles = line.split(QLatin1Char(' '), QString::SkipEmptyParts);
      }
      line.replace(QLatin1Char(' '), QLatin1Char('-'));
      line = line.toLower();

      // qDebug().noquote() << "File: " << fileInfo.completeBaseName()
      //                    << "\n Raw:\t" << raw
      //                    << "\n Unref:\t" << unref
      //                    << "\n Titles:\t" << titles
      //                    << "\n link:\t" << line;

      for (auto&& title : titles) {
        titleMap->insert(title, {unref, line});
      }
      count += titles.count();
    }
  };

  // Add tasks to thread pool
  QVector<QMultiMap<QString, QPair<QString, QString>>> titles;
  titles.resize(files.count());
  futures.reserve(files.count());
  auto now = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < files.count(); ++i) {
    futures.emplace_back(
        ThreadPool::default_pool().AddTask(IndexFile, files.at(i), &titles[i]));
    if ((std::chrono::high_resolution_clock::now() - now) > kFrameInterval) {
      QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
      now = std::chrono::high_resolution_clock::now();
    }
  }

  for (int i = 0; i < files.count(); ++i) {
    // Wait future
    std::future_status status;
    do {
      QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
      status = futures[i].wait_for(kFrameInterval);
    } while (status != std::future_status::ready);
    futures[i].get();

    // Add result to model
    model_->titles_[files.at(i).completeBaseName()] = titles.at(i);

    // Update progress
    progress.setValue(progress.value() + 1);
  }

  model_->endResetModel();

  return count.load();
}

void IndexLauncher::raise() {
  if (isVisible()) {
    hide();
    return;
  }

  model_->SelectFile();
  input_->clear();
  input_->setPlaceholderText(tr("Please enter file name or class name"));
  emit input_->textChanged({});

  show();
  QWidget::raise();
  input_->setFocus();

  QWindow* window = windowHandle();
  if (window) {
    QScreen* screen = window->screen();
    QRect sGeom = screen->geometry();
    setFixedWidth(std::max(kMinWidth, sGeom.width() / 2));
    QRect geom = geometry();
    geom.moveCenter(sGeom.center());
    setGeometry(geom);
  }
  window->setOpacity(kOpacity);
}

bool IndexLauncher::eventFilter(QObject* object, QEvent* event) {
  static constexpr int kPageIndexes = 5;

  if (event->type() == QEvent::KeyRelease) {
    switch (dynamic_cast<QKeyEvent*>(event)->key()) {
      case Qt::Key_Escape:
        hide();
        break;

      case Qt::Key_Up: {
        int row = filter_->mapFromSource(model_->currentIndex_).row() - 1;
        row = (row < 0) ? (filter_->rowCount() - 1) : row;
        model_->Select(filter_->mapToSource(filter_->index(row, 0)));
      } break;

      case Qt::Key_Down: {
        int row = filter_->mapFromSource(model_->currentIndex_).row() + 1;
        row %= filter_->rowCount();
        model_->Select(filter_->mapToSource(filter_->index(row, 0)));
      } break;

      case Qt::Key_PageUp: {
        int row =
            filter_->mapFromSource(model_->currentIndex_).row() - kPageIndexes;
        row = (row < 0) ? 0 : row;
        model_->Select(filter_->mapToSource(filter_->index(row, 0)));
      } break;

      case Qt::Key_PageDown: {
        int row =
            filter_->mapFromSource(model_->currentIndex_).row() + kPageIndexes;
        row = (row >= filter_->rowCount()) ? (filter_->rowCount() - 1) : row;
        model_->Select(filter_->mapToSource(filter_->index(row, 0)));
      } break;

      case Qt::Key_Return:
      case Qt::Key_Enter: {
        if (model_->file_.isEmpty()) {
          model_->SelectFile(model_->currentIndex_.data().toString());
          input_->setPlaceholderText(tr("Please enter title"));
          input_->clear();
        } else {
          model_->CopyCurrent();
          hide();
        }
      } break;

      default:
        break;
    }
  }
  return QFrame::eventFilter(object, event);
}
