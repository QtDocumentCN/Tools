#include "indexlauncher.h"

#include <atomic>
#include <chrono>
#include <iterator>
#include <vector>

#include <QtCore/QAbstractTableModel>
#include <QtCore/QBitArray>
#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QRegularExpression>
#include <QtCore/QVector>
#include <QtCore/QMultiHash>
#include <QtCore/QSortFilterProxyModel>
#include <QtGui/QAbstractTextDocumentLayout>
#include <QtGui/QClipboard>
#include <QtGui/QGuiApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtGui/QPainter>
#include <QtGui/QScreen>
#include <QtGui/QTextDocument>
#include <QtGui/QKeyEvent>
#include <QtGui/QWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStyledItemDelegate>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/private/qframe_p.h>

#include "threadpool.h"

using namespace std::literals::chrono_literals;

static const QString kStyleSheets = QStringLiteral("border: none;");
static constexpr int kMinWidth = 500;
static constexpr double kOpacity = 0.8;

static constexpr auto kFrameInterval = 10ms;

/* ================ IndexLauncherPrivate ================ */
class IndexLauncherPrivate : public QFramePrivate,
                             public QAbstractListModel,
                             public QStyledItemDelegate {
  Q_DECLARE_PUBLIC(IndexLauncher)
 public:
  static bool IsQtClassName(const QString& file);
  static QString FilePath(QString file);
  static void IndexFile(const QFileInfo& fileInfo,
                        QMultiHash<QString, QPair<QString, QString>>* titleMap,
                        std::atomic<size_t>* count);

  void UpdateIndexes(
      const QFileInfoList& files,
      const QVector<QMultiHash<QString, QPair<QString, QString>>>& titles);
  bool SelectFile(const QString& file = {});
  void Select(int row);
  QString CurrentFile() const;
  QString CurrentTitle() const;
  QModelIndex CurrentIndex() const;

  // QAbstractListModel
  // https://stackoverflow.com/questions/1956542/how-to-make-item-view-render-rich-html-text-in-qt
  int rowCount(const QModelIndex& parent) const override;
  QVariant data(const QModelIndex& index, int role) const override;

  // QStyledItemDelegate
  void paint(QPainter* painter, const QStyleOptionViewItem& option,
             const QModelIndex& index) const override;
  QSize sizeHint(const QStyleOptionViewItem& option,
                 const QModelIndex& index) const override;

 private:
  QLineEdit* input_ = nullptr;
  QListView* list_ = nullptr;
  QSortFilterProxyModel* filter_ = nullptr;

  // <File, <Title, (Text, Link)>>
  QHash<QString, QMultiHash<QString, QPair<QString, QString>>> titles_;
  QString currentFile_;
};

bool IndexLauncherPrivate::IsQtClassName(const QString& file) {
  return (file.length() > 1) && (file.at(0) == QLatin1Char('Q')) &&
         (file.at(1).isUpper());
}

QString IndexLauncherPrivate::FilePath(QString file) {
  if (file.isEmpty()) {
    return {};
  }
  if (file.endsWith(QStringLiteral(".md"))) {
    file = file.left(file.length() - 3);
  }
  QChar ch = IsQtClassName(file) ? file.at(1) : file.at(0);
  return QStringLiteral("../../%1/%2/%2.md").arg(ch.toUpper()).arg(file);
}

void IndexLauncherPrivate::IndexFile(
    const QFileInfo& fileInfo,
    QMultiHash<QString, QPair<QString, QString>>* titleMap,
    std::atomic<size_t>* count) {
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
    // QString raw = line;

    // Remove syntax and strings * = " \ ' /
    // [\*\=\"\\\'\/]
    static const auto kSyntaxRegexp = [] {
      auto regexp =
          QRegularExpression{QStringLiteral("[\\*\\=\\\"\\\\\\'\\/]")};
      regexp.optimize();
      return regexp;
    }();
    line.replace(kSyntaxRegexp, QString{});

    // Replace markdown link [xxx](yyy) to xxx
    // \[(\S+)\]\(\S+\)
    static const auto kLinkRegexp = [] {
      auto regexp =
          QRegularExpression{QStringLiteral("\\[(\\S+)\\]\\(\\S+\\)")};
      regexp.optimize();
      return regexp;
    }();
    line.replace(kLinkRegexp, QStringLiteral("\\1"));
    QString unref = line;

    // Find function name
    //[\w_]+::([\w_]+)\(
    static const auto kMethodRegexp = [] {
      auto regexp = QRegularExpression{QStringLiteral("[\\w_]+::([\\w_]+)\\(")};
      regexp.optimize();
      return regexp;
    }();
    QStringList titles;
    QRegularExpressionMatch match = kMethodRegexp.match(line);
    if (match.hasMatch()) {
      titles << match.captured(1);
    }

    // No function name, find other symbols
    // [\w_]+::([\w_]+)
    static const auto kMemberRegexp = [] {
      QRegularExpression regexp{QStringLiteral("[\\w_]+::([\\w_]+)")};
      regexp.optimize();
      return regexp;
    }();
    if (titles.isEmpty()) {
      QRegularExpressionMatchIterator it = kMemberRegexp.globalMatch(line);
      while (it.hasNext()) {
        titles << it.next().captured(1);
      };
    }

    // Generate html link _ , . : ( ) [ ] { }
    // [\_\,\.\:\(\)\[\]\{\}]
    static const auto kPunctuationRegexp = [] {
      QRegularExpression regexp{
          QStringLiteral("[\\_\\,\\.\\:\\(\\)\\[\\]\\{\\}]")};
      regexp.optimize();
      return regexp;
    }();
    line.replace(kPunctuationRegexp, QString{});
    line.replace(QLatin1Char('\t'), QLatin1Char('-'));
    if (titles.isEmpty()) {
      titles = line.split(QLatin1Char(' '), Qt::SkipEmptyParts);
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
    count->fetch_add(titles.count());
  }
}

void IndexLauncherPrivate::UpdateIndexes(
    const QFileInfoList& files,
    const QVector<QMultiHash<QString, QPair<QString, QString>>>& titles) {
  QSignalBlocker blocker(input_);
  beginResetModel();
  for (int i = 0; i < files.count(); ++i) {
    titles_[files.at(i).completeBaseName()] = titles.at(i);
  }
  currentFile_.clear();
  input_->clear();
  endResetModel();
  filter_->sort(0);
}

bool IndexLauncherPrivate::SelectFile(const QString& file) {
  input_->setText(file);
  beginResetModel();
  auto it = titles_.find(file);
  currentFile_ = (it == titles_.cend()) ? QString{} : file;
  input_->setPlaceholderText(
      (it == titles_.cend())
          ? IndexLauncher::tr("Please enter file name or class name")
          : IndexLauncher::tr("Please enter title"));
  endResetModel();
  filter_->sort(0);
  return it != titles_.cend();
}

void IndexLauncherPrivate::Select(int row) {
  auto index = filter_->index(row, 0);
  if (index.isValid()) {
    list_->selectionModel()->select(index, QItemSelectionModel::SelectCurrent);
    list_->scrollTo(index);
  }
}

QString IndexLauncherPrivate::CurrentFile() const {
  QModelIndex index = CurrentIndex();
  if (!index.isValid()) {
    // Fetch file name from previouts output ../../x/xxx/xxx.md#xxx
    auto list = input_->text().split(QLatin1Char('/'), Qt::SkipEmptyParts);
    if (!list.isEmpty()) {
      list = list.last().split(QLatin1Char('\\'), Qt::SkipEmptyParts);
    }
    if (!list.isEmpty()) {
      list = list.first().split(QLatin1Char('#'), Qt::SkipEmptyParts);
    }
    return list.isEmpty() ? QString{} : list.first();
  }
  index = filter_->mapToSource(index);
  auto it = titles_.cbegin();
  std::advance(it, index.row());
  return it.key();
}

QString IndexLauncherPrivate::CurrentTitle() const {
  if (currentFile_.isEmpty()) {
    return {};
  }
  auto index = CurrentIndex();
  if (!index.isValid()) {
    return QString{};
  } else {
    auto it = titles_[currentFile_].cbegin();
    std::advance(it, filter_->mapToSource(index).row());
    return it->second;
  }
}

QModelIndex IndexLauncherPrivate::CurrentIndex() const {
  auto selected = list_->selectionModel()->selectedIndexes();
  return selected.isEmpty() ? QModelIndex{} : selected.first();
}

int IndexLauncherPrivate::rowCount(const QModelIndex&) const {
  return currentFile_.isEmpty() ? titles_.count()
                                : titles_[currentFile_].count();
}

QVariant IndexLauncherPrivate::data(const QModelIndex& index, int role) const {
  switch (role) {
    case Qt::DisplayRole:
      if (currentFile_.isEmpty()) {
        auto it = titles_.cbegin();
        std::advance(it, index.row());
        return it.key();
      } else {
        auto it = titles_[currentFile_].cbegin();
        std::advance(it, index.row());
        return QStringLiteral("**%1**\n%2").arg(it.key(), it->first);
      }

    default:
      break;
  }
  return {};
}

void IndexLauncherPrivate::paint(QPainter* painter,
                                 const QStyleOptionViewItem& option,
                                 const QModelIndex& index) const {
  QStyleOptionViewItem options = option;
  initStyleOption(&options, index);

  painter->save();

  QTextDocument doc;
  doc.setMarkdown(options.text);

  options.text.clear();
  options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options,
                                       painter);

  // shift text right to make icon visible
  QSize iconSize = options.icon.actualSize(options.rect.size());
  painter->translate(options.rect.left() + iconSize.width(),
                     options.rect.top());
  QRect clip(0, 0, options.rect.width() + iconSize.width(),
             options.rect.height());

  // doc.drawContents(painter, clip);

  painter->setClipRect(clip);
  QAbstractTextDocumentLayout::PaintContext ctx;
  // set text color to red for selected item
  //  if (option.state & QStyle::State_Selected)
  //    ctx.palette.setColor(QPalette::Text, QColor("red"));
  ctx.clip = clip;
  doc.documentLayout()->draw(painter, ctx);

  painter->restore();
}

QSize IndexLauncherPrivate::sizeHint(const QStyleOptionViewItem& option,
                                     const QModelIndex& index) const {
  QStyleOptionViewItem options = option;
  initStyleOption(&options, index);

  QTextDocument doc;
  doc.setMarkdown(options.text);
  doc.setTextWidth(options.rect.width());
  return {int(doc.idealWidth()), int(doc.size().height())};
}
/* ================ IndexLauncherPrivate ================ */

/* ================ IndexLauncher ================ */
IndexLauncher::IndexLauncher(QWidget* parent, Qt::WindowFlags flags)
    : QFrame(*(new IndexLauncherPrivate), parent, flags) {
  Q_D(IndexLauncher);

  d->input_ = new QLineEdit(this);
  d->list_ = new QListView(this);
  d->filter_ = new QSortFilterProxyModel(this);

  auto layout = new QVBoxLayout(this);

  d->input_->setStyleSheet(kStyleSheets);
  d->input_->installEventFilter(this);
  layout->addWidget(d->input_);

  auto line = new QFrame(this);
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  layout->addWidget(line);

  d->filter_->setSourceModel(d);
  d->filter_->setFilterCaseSensitivity(Qt::CaseInsensitive);
  d->list_->setModel(d->filter_);
  d->list_->setItemDelegate(d);
  auto palette = d->list_->palette();
  palette.setColor(QPalette::Highlight, QColor(QStringLiteral("royalblue")));
  d->list_->setPalette(palette);
  d->list_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  d->list_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  d->list_->setStyleSheet(kStyleSheets);
  d->list_->setSelectionMode(QAbstractItemView::NoSelection);
  layout->addWidget(d->list_);

  connect(d->input_, &QLineEdit::textChanged, this,
          [this](const QString& text) {
            Q_D(IndexLauncher);
            d->filter_->setFilterFixedString(text);
            d->Select(0);
          });
}

size_t IndexLauncher::IndexFiles(const QFileInfoList& files) {
  Q_D(IndexLauncher);

  hide();

  std::vector<std::future<void>> futures;
  std::atomic<size_t> count = ATOMIC_VAR_INIT(0);

  QProgressBar progress;
  progress.setTextVisible(false);
  progress.setMaximum(files.count() - 1);
  progress.setWindowFlags(Qt::Tool | Qt::FramelessWindowHint |
                          Qt::WindowStaysOnTopHint);
  progress.show();

  // Add tasks to thread pool
  QVector<QMultiHash<QString, QPair<QString, QString>>> titles;
  titles.resize(files.count());
  futures.reserve(files.count());
  auto now = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < files.count(); ++i) {
    futures.emplace_back(ThreadPool::default_pool().AddTask(
        IndexLauncherPrivate::IndexFile, files.at(i), &titles[i], &count));
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

    // Update progress
    progress.setValue(progress.value() + 1);
  }

  // Add result to model
  d->UpdateIndexes(files, titles);

  // Item height for first display is wrong, so trigger & hide to recalculate.
  Trigger();
  hide();

  return count.load();
}

void IndexLauncher::Trigger() {
  Q_D(IndexLauncher);

  // Copy selected link
  if (isVisible()) {
    if (d->currentFile_.isEmpty()) {  // File selection mode
      QGuiApplication::clipboard()->setText(
          IndexLauncherPrivate::FilePath(d->CurrentFile()));
    } else {  // Title selection mode
      QGuiApplication::clipboard()->setText(QStringLiteral("#") +
                                            d->CurrentTitle());
    }
    hide();
    return;
  }

  // Clear selection
  d->SelectFile(QString{});

  // Update selection from user's clipboard
  QStringList list = QGuiApplication::clipboard()->text().split(
      QStringLiteral("::"), Qt::SkipEmptyParts);
  QString file = list.isEmpty() ? QString{} : list.first();
  if (IndexLauncherPrivate::IsQtClassName(file)) {  // Valid class name
    if (list.count() > 1) {                         // Has title
      if (d->SelectFile(file)) {                    // File is valid
        d->input_->setText(list.at(1));
      }
    } else {  // File only
      d->input_->setText(file);
    }
  } else if (file.endsWith(QStringLiteral(".md"))) {  // .md file
    d->input_->setText(file.mid(0, file.length() - 3));
  } else {  // Invalid clipboard text
    d->input_->setText(file);
  }
  emit d->input_->textChanged(d->input_->text());

  // Launch GUI
  show();
  QWidget::raise();
  d->input_->setFocus();

  // Move to screen center
  QWindow* window = windowHandle();
  if (window) {
    QScreen* screen = window->screen();
    QRect sGeom = screen->geometry();
    setFixedWidth(std::max(kMinWidth, sGeom.width() / 2));
    QRect geom = geometry();
    geom.moveCenter(sGeom.center());
    setGeometry(geom);
    window->setOpacity(kOpacity);
  }
}

bool IndexLauncher::eventFilter(QObject* object, QEvent* event) {
  static constexpr int kPageIndexes = 5;

  Q_D(IndexLauncher);

  if (event->type() == QEvent::KeyPress) {
    auto e = dynamic_cast<QKeyEvent*>(event);
    switch (e->key()) {
      case Qt::Key_Escape:
        hide();
        break;

      case Qt::Key_Up: {
        int row = d->CurrentIndex().row() - 1;
        row = (row < 0) ? (d->filter_->rowCount() - 1) : row;
        d->Select(row);
      } break;

      case Qt::Key_Down: {
        int row = d->CurrentIndex().row() + 1;
        row %= d->filter_->rowCount();
        d->Select(row);
      } break;

      case Qt::Key_PageUp: {
        int row = d->CurrentIndex().row() - kPageIndexes;
        row = (row < 0) ? 0 : row;
        d->Select(row);
      } break;

      case Qt::Key_PageDown: {
        int row = d->CurrentIndex().row() + kPageIndexes;
        row = (row >= d->filter_->rowCount()) ? (d->filter_->rowCount() - 1)
                                              : row;
        d->Select(row);
      } break;

      case Qt::Key_Return:
      case Qt::Key_Enter: {
        if (d->currentFile_.isEmpty()) {  // File selection mode
          auto index = d->CurrentIndex();
          if (index.isValid()) {
            d->SelectFile(index.data().toString());
            d->input_->clear();
          }
        } else {  // Title selection mode
          QGuiApplication::clipboard()->setText(QStringLiteral("%1#%2").arg(
              IndexLauncherPrivate::FilePath(d->currentFile_),
              d->CurrentTitle()));
          hide();
        }
      } break;

      default:
        break;
    }
  }
  return QFrame::eventFilter(object, event);
}
/* ================ IndexLauncher ================ */
