#include "searchpopup.h"

#include <chrono>
#include <list>

#include <QtCore/QAbstractTableModel>
#include <QtCore/QBitArray>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QMutex>
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

#include "thread.h"
#include <QTime>

using namespace std::literals::chrono_literals;
class Model : public QAbstractListModel {
  friend class SearchPopup;

 public:
  explicit Model(QObject* parent = nullptr);

  void SelectFile(const QString& file = {});
  void Select(const QModelIndex& index);
  void CopyCurrent();

  virtual int rowCount(const QModelIndex& parent) const override;
  virtual QVariant data(const QModelIndex& index, int role) const override;

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

  QListView* list = qobject_cast<QListView*>(parent());
  QSortFilterProxyModel* filter =
      qobject_cast<QSortFilterProxyModel*>(list->model());
  list->scrollTo(filter->mapFromSource(currentIndex_));
}

void Model::CopyCurrent() {
  QString text =
      QStringLiteral("../../%1/%2/%2.md#%3")
          .arg(file_.front().toUpper())
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

SearchPopup::SearchPopup(QWidget* parent, Qt::WindowFlags flags)
    : QFrame(parent, flags),
      input_(new QLineEdit(this)),
      list_(new QListView(this)),
      model_(new Model(list_)),
      filter_(new QSortFilterProxyModel(list_)) {
  static const QString styleSheets = QStringLiteral("border: none;");
  auto layout = new QVBoxLayout(this);

  input_->setStyleSheet(styleSheets);
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
  list_->setStyleSheet(styleSheets);
  list_->setSelectionMode(QAbstractItemView::NoSelection);
  layout->addWidget(list_);

  connect(input_, &QLineEdit::textChanged, [this](const QString& text) {
    filter_->setFilterFixedString(text);
    model_->Select(filter_->mapToSource(filter_->index(0, 0)));
  });
}

size_t SearchPopup::IndexFiles(const QStringList& files) {
  model_->beginResetModel();
  model_->titles_.clear();

  QMutex mutex;
  std::list<std::future<void>> futures;
  size_t count = 0;

  QProgressBar progress;
  progress.setTextVisible(false);
  progress.setMaximum(files.count() - 1);
  progress.setWindowFlags(Qt::Tool | Qt::FramelessWindowHint |
                          Qt::WindowStaysOnTopHint);
  progress.show();

  std::function<void(const QFileInfo&)> IndexFile =
      [this, &mutex, &count](const QFileInfo& fileInfo) {
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

          // Remove syntax and strings * = " \ ' / with [\*\=\"\\\'\/]
          line.replace(
              QRegularExpression{QStringLiteral("[\\*\\=\\\"\\\\\\'\\/]")},
              QString{});

          // Replace markdown link [xxx](yyy) to xxx with \[(\S+)\]\(\S+\)
          line.replace(
              QRegularExpression{QStringLiteral("\\[(\\S+)\\]\\(\\S+\\)")},
              QStringLiteral("\\1"));
          QString unref = line;

          // Find function name with [\w_]+::([\w_]+)\(
          QStringList titles;
          QRegularExpressionMatch match =
              QRegularExpression{QStringLiteral("[\\w_]+::([\\w_]+)\\(")}.match(
                  line);
          if (match.hasMatch()) {
            titles << match.captured(1);
          }

          // No function name, find other symbols with [\w_]+::([\w_]+)
          if (titles.isEmpty()) {
            QRegularExpressionMatchIterator it =
                QRegularExpression{QStringLiteral("[\\w_]+::([\\w_]+)")}
                    .globalMatch(line);
            while (it.hasNext()) {
              QRegularExpressionMatch match = it.next();
              titles << match.captured(1);
            };
          }

          // Generate html link _ , . : ( ) [ ] { } with
          // [\_\,\.\:\(\)\[\]\{\}]
          line.replace(QRegularExpression{QStringLiteral(
                           "[\\_\\,\\.\\:\\(\\)\\[\\]\\{\\}]")},
                       QString{});
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

          QMutexLocker locker(&mutex);
          for (auto&& title : titles) {
            model_->titles_[fileInfo.completeBaseName()].insert(title,
                                                                {unref, line});
          }
          count += titles.size();
        }
      };

  std::future<void> IndexProcess =
      std::async([&files, &mutex, &futures, &IndexFile] {
        for (auto&& file : files) {
          QFileInfo fileInfo{file};
          QMutexLocker locker(&mutex);
          futures.emplace_back(
              ThreadPool::default_pool().AddTask(IndexFile, fileInfo));
        }
      });

  for (int i = 0; i < files.count(); ++i) {
    // Get future
    while (futures.empty()) {
    }
    std::future<void>* future;
    {
      QMutexLocker locker(&mutex);
      future = &futures.front();
    }

    // Wait future
    std::future_status status;
    do {
      status = future->wait_for(10ms);
      qApp->processEvents();
    } while (status != std::future_status::ready);
    future->get();

    // Update progress
    progress.setValue(progress.value() + 1);
    QMutexLocker locker(&mutex);
    futures.pop_front();
  }

  IndexProcess.get();

  model_->endResetModel();

  return count;
}

void SearchPopup::raise() {
  if (isVisible()) {
    hide();
    return;
  }

  model_->SelectFile();
  input_->clear();
  input_->setPlaceholderText(QStringLiteral("请输入类名/文件名"));
  emit input_->textChanged({});

  show();
  QWidget::raise();
  input_->setFocus();

  QWindow* window = windowHandle();
  if (window) {
    QScreen* screen = window->screen();
    QRect sGeom = screen->geometry();
    setFixedWidth(std::max(500, sGeom.width() / 2));
    QRect geom = geometry();
    geom.moveCenter(sGeom.center());
    setGeometry(geom);
  }
  window->setOpacity(0.8);
}

bool SearchPopup::eventFilter(QObject* object, QEvent* event) {
  if (event->type() == QEvent::KeyRelease) {
    switch (static_cast<QKeyEvent*>(event)->key()) {
      case Qt::Key_Escape:
        hide();
        break;

      case Qt::Key_Up:
      {
        int row = filter_->mapFromSource(model_->currentIndex_).row() - 1;
        row = (row < 0) ? (filter_->rowCount() - 1) : row;
        model_->Select(filter_->mapToSource(filter_->index(row, 0)));
      }
        break;

      case Qt::Key_Down:
      {
        int row = filter_->mapFromSource(model_->currentIndex_).row() + 1;
        row %= filter_->rowCount();
        model_->Select(filter_->mapToSource(filter_->index(row, 0)));
      }
      break;

      case Qt::Key_PageUp:
      {
        int row = filter_->mapFromSource(model_->currentIndex_).row() - 5;
        row = (row < 0) ? 0 : row;
        model_->Select(filter_->mapToSource(filter_->index(row, 0)));
      }
      break;

      case Qt::Key_PageDown:
      {
        int row = filter_->mapFromSource(model_->currentIndex_).row() + 5;
        row = (row >= filter_->rowCount()) ? (filter_->rowCount() - 1) : row;
        model_->Select(filter_->mapToSource(filter_->index(row, 0)));
      }
      break;

      case Qt::Key_Return:
      case Qt::Key_Enter:
      {
        if (model_->file_.isEmpty()) {
          model_->SelectFile(model_->currentIndex_.data().toString());
          input_->setPlaceholderText(QStringLiteral("请输入标题"));
          input_->clear();
        } else {
          model_->CopyCurrent();
          hide();
        }
      }
      break;

      default:
        break;
    }
  }
  return QFrame::eventFilter(object, event);
}
