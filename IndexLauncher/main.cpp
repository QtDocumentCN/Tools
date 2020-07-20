#include <functional>

#include <QtCore/QElapsedTimer>
#include <QtCore/QFileInfo>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>
#include <QtCore/QTimer>
#include <QtCore/QSettings>
#include <QtCore/QUrl>
#include <QtGui/QColor>
#include <QtGui/QDesktopServices>
#include <QtGui/QIcon>
#include <QtGui/QPalette>
#include <QtGui/QScreen>
#include <QtGui/QWindow>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMenu>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStyleFactory>
#include <QtWidgets/QSystemTrayIcon>

#include <QHotkey>

#include "indexlauncher.h"
#include "shortcutinput.hpp"

static const QString kFramelessBlurStyleSheets = QStringLiteral(
    "background-color: #aa000000;"
    "color: white;"
    "border: 1px solid royalblue;");
static constexpr double kOpacity = 0.8;
static constexpr int kCloseDelay = 250;
static constexpr int kInformationTime = 5000;
static constexpr QSize kHelpIconSize{64, 64};

static const QString kOrganizationUrl =
    QStringLiteral("https://github.com/QtDocumentCN");
static const QString kBsdUrl = QStringLiteral(
    "https://tldrlegal.com/license/bsd-3-clause-license-(revised)");

void ShowHelp(const QString& shortcut) {
  QDialog dialog{nullptr, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint};
  dialog.setWindowTitle(IndexLauncher::tr("Help"));

  auto layout = new QVBoxLayout(&dialog);

  {
    auto title_layout = new QHBoxLayout;
    title_layout->setAlignment(Qt::AlignLeft);
    layout->addLayout(title_layout);

    auto icon = new QLabel(&dialog);
    icon->setPixmap(QApplication::windowIcon().pixmap(kHelpIconSize));
    title_layout->addWidget(icon);

    auto title =
        new QLabel(IndexLauncher::tr("# Markdown Index Launcher\n"), &dialog);
    title->setTextFormat(Qt::MarkdownText);
    title_layout->addWidget(title);
  }

  auto text = new QLabel(&dialog);
  text->setTextFormat(Qt::MarkdownText);
  text->setTextInteractionFlags(Qt::TextBrowserInteraction);
  text->setText(IndexLauncher::tr("\
This tool can index markdown files, and help you to search titles, retrieve it's link into clipboard.\n\
\n----\n\
\n## Index path\n\
- File link generation:\n\
    1. Press `%1` to open the index launcher, class/file name in clipboard will be auto filled.\n\
    2. Enter class/file name, select correspond item with Up/Down or PageUp/PageDown keys.\n\
    3. Press `%1`, the link will be generated into clipboard.\n\
- Title link generation\n\
    1. Press `%1` to open the index launcher, class/file name in clipboard will be auto filled.\n\
    2. Enter class/file name, select correspond item with Up/Down or PageUp/PageDown keys.\n\
    3. Press `Enter`, then the list will show titles under the class/file.\n\
    4. Select correspond title in same way.\n\
        - Press `Enter`, `file#title` link will be generated into clipboard.\n\
        - Press `%1`, `#title` link will be generated into clipboard.\n\
\n## Set hotkey\n\
Set hotkey for index launcher, current is `%1`.\n\
\n----\n\
\nCopyleft [QtDocumentCN](%2) with [3-Clause BSD License](%3).")
                    .arg(shortcut, kOrganizationUrl, kBsdUrl));
  layout->addWidget(text);

  {
    auto button_layout = new QHBoxLayout;
    button_layout->setAlignment(Qt::AlignRight);
    layout->addLayout(button_layout);

    auto about_qt = new QPushButton(IndexLauncher::tr("About &Qt..."), &dialog);
    button_layout->addWidget(about_qt);
    QObject::connect(about_qt, &QPushButton::clicked, &QApplication::aboutQt);

    auto ok = new QPushButton(IndexLauncher::tr("&Ok"), &dialog);
    button_layout->addWidget(ok);
    ok->setFocus();
    QObject::connect(ok, &QPushButton::clicked, &dialog, &QDialog::accept);
  }

  dialog.exec();
}

int main(int argc, char* argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);

  // Install translator
  QTranslator translator_zh_CN;
  if (translator_zh_CN.load(
          QLocale(QLocale::Chinese),
          QStringLiteral(":/translation/IndexLauncher_zh_CN.qm"))) {
    QCoreApplication::installTranslator(&translator_zh_CN);
  }

  QCoreApplication::setApplicationName(QStringLiteral("IndexLauncher"));
  QCoreApplication::setOrganizationName(QStringLiteral("QtDocumentCN"));
  QGuiApplication::setQuitOnLastWindowClosed(false);
  QApplication::setWindowIcon(QIcon(QStringLiteral(":/icon/tools.ico")));

#ifdef Q_OS_WIN
  // https://forum.qt.io/topic/101391/windows-10-dark-theme/4
  QSettings reg(QStringLiteral("HKEY_CURRENT_"
                               "USER\\Software\\Microsoft\\Windows\\CurrentVers"
                               "ion\\Themes\\Personalize"),
                QSettings::NativeFormat);
  if (reg.value(QStringLiteral("AppsUseLightTheme")) == 0) {
    QApplication::setStyle(QStyleFactory::create(QStringLiteral("Fusion")));
    QPalette darkPalette;
    static const QColor kDarkColor = QColor(43, 43, 43);
    static const QColor kDisabledColor = QColor(127, 127, 127);
    static const QColor kBaseColor = QColor(30, 30, 30);
    static const QColor kLinkColor = QColor(0, 153, 188);
    static const QColor kHighlightColor = QColor(65, 65, 65);
    darkPalette.setColor(QPalette::Window, kDarkColor);
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, kBaseColor);
    darkPalette.setColor(QPalette::AlternateBase, kDarkColor);
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, kDisabledColor);
    darkPalette.setColor(QPalette::Button, kDarkColor);
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText,
                         kDisabledColor);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, kLinkColor);
    darkPalette.setColor(QPalette::Highlight, kHighlightColor);
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText,
                         kDisabledColor);
    QApplication::setPalette(darkPalette);
    app.setStyleSheet(QStringLiteral(
        "QWidget:window { border: 1px solid #a0a0a0; } "
        "QMenu { border: 1px solid #a0a0a0; } "
        "QMenu::separator { height: 1px; margin: 5px 10px 5px 10px; "
        "background: #808080} "
        "QToolTip { color: #ffffff; background-color: #2a82da; "
        "border: 1px solid #a0a0a0; }"));
  }
#endif

  // Read shortcut from settings
  QSettings settings(QStringLiteral("config.ini"), QSettings::IniFormat);
  QString shortcut =
      settings.value(QStringLiteral("ShortCut"), QStringLiteral("Ctrl+Shift+C"))
          .toString();

  // Initialize tray icon
  QSystemTrayIcon tray;
  tray.setIcon(QApplication::windowIcon());
  QMenu menu;

  // Initialize popup window
  IndexLauncher launcher{nullptr, Qt::SplashScreen | Qt::FramelessWindowHint |
                                      Qt::WindowStaysOnTopHint};
  launcher.setStyleSheet(kFramelessBlurStyleSheets);

  // Initialize global hotkey
  QHotkey hotkey{QKeySequence{shortcut, QKeySequence::PortableText}};
  QObject::connect(&hotkey, &QHotkey::activated, &launcher,
                   &IndexLauncher::Trigger);

  // Reset hotkey
  auto ResetHotkey = [&shortcut, &tray, &hotkey,
                      &launcher](const QString& keys) -> bool {
    launcher.hide();
    hotkey.setRegistered(false);
    hotkey.setShortcut(QKeySequence{keys, QKeySequence::PortableText});
    bool hotkeyRegistered = hotkey.isRegistered();
    if (hotkeyRegistered) {
      tray.showMessage(
          IndexLauncher::tr("Markdown Index Launcher"),
          IndexLauncher::tr("Hotkey %1 is already used!").arg(keys),
          QSystemTrayIcon::Warning);
    } else {
      shortcut = keys;
      tray.showMessage(IndexLauncher::tr("Markdown Index Launcher"),
                       IndexLauncher::tr("Hotkey is set to %1").arg(keys),
                       QSystemTrayIcon::Information, kInformationTime);
    }
    hotkey.setShortcut(shortcut, true);
    return !hotkeyRegistered;
  };

  // Action - index path
  QObject::connect(
      menu.addAction(IndexLauncher::tr("&Indexing path...")),
      &QAction::triggered, &menu, [&settings, &tray, &launcher] {
        // Recursively traverse dirctory tree
        std::function<void(QFileInfoList&, const QString&)> Traversal =
            [&Traversal](QFileInfoList& files, const QString& d) {
              QFileInfoList list = QDir{d}.entryInfoList(
                  QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
              for (auto&& info : list) {
                if (info.isFile()) {
                  files << info;
                } else if (info.isDir()) {
                  Traversal(files, info.absoluteFilePath());
                }
              }
            };

        static const QString kDir = QStringLiteral("Dir");
        QString dir = settings.value(kDir).toString();
        QString d = QFileDialog::getExistingDirectory(
            nullptr, IndexLauncher::tr("Indexing path"), dir);
        if (!d.isEmpty()) {
          QFileInfoList files;
          dir = d;
          settings.setValue(kDir, d);
          settings.sync();
          Traversal(files, d);
          QElapsedTimer timer;
          timer.start();
          size_t count = launcher.IndexFiles(files);
          tray.showMessage(
              IndexLauncher::tr("Markdown Index Launcher"),
              IndexLauncher::tr(
                  "Index finised for %1 files with %2 titles in %3 ms")
                  .arg(files.count())
                  .arg(count)
                  .arg(timer.elapsed()),
              QSystemTrayIcon::Information, kInformationTime);
        }
      });

  // Action - set shortcut
  QObject::connect(
      menu.addAction(IndexLauncher::tr("&Set hotkey")), &QAction::triggered,
      &menu, [&settings, &shortcut, &hotkey, &ResetHotkey] {
        auto input = new ShortcutInput(
            QKeySequence(shortcut, QKeySequence::PortableText), nullptr,
            Qt::SplashScreen | Qt::FramelessWindowHint |
                Qt::WindowStaysOnTopHint);
        input->setAttribute(Qt::WA_DeleteOnClose);
        input->setStyleSheet(kFramelessBlurStyleSheets +
                             QStringLiteral("padding: 5px; font: 28pt;"));

        QObject::connect(
            input, &ShortcutInput::finished, input,
            [&settings, &shortcut, &ResetHotkey, input](const QString& keys) {
              if (ResetHotkey(keys)) {
                shortcut = keys;
                settings.setValue(QStringLiteral("ShortCut"), shortcut);
                settings.sync();
              }
              QTimer::singleShot(kCloseDelay, input, SLOT(deleteLater()));
            });

        hotkey.setRegistered(false);
        input->resize(input->sizeHint());
        input->show();
        input->raise();
        input->setFocus();

        QWindow* window = input->windowHandle();
        if (window) {
          QScreen* screen = window->screen();
          QRect geom = input->geometry();
          geom.moveCenter(screen->geometry().center());
          input->setGeometry(geom);
          window->setOpacity(kOpacity);
        }
      });

  menu.addSeparator();

  // Action - help
  QObject::connect(menu.addAction(IndexLauncher::tr("&Help")),
                   &QAction::triggered, &menu,
                   [&shortcut] { ShowHelp(shortcut); });

  // Action - homepage
  QObject::connect(menu.addAction(IndexLauncher::tr("Ho&mepage")),
                   &QAction::triggered,
                   [] { QDesktopServices::openUrl(QUrl{kOrganizationUrl}); });

  // Action - exit
  QObject::connect(menu.addAction(IndexLauncher::tr("&Quit")),
                   &QAction::triggered, [] { QCoreApplication::exit(); });

  // Shot tray icon
  tray.setContextMenu(&menu);
  tray.show();
  ResetHotkey(shortcut);

  return QApplication::exec();
}
