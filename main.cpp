#include <functional>

#include <QtCore/QElapsedTimer>
#include <QtCore/QFileInfo>
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
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMenu>
#include <QtWidgets/QStyleFactory>
#include <QtWidgets/QSystemTrayIcon>

#include <QHotkey>

#include "searchpopup.h"
#include "shortcutinput.hpp"

static const QString kFramelessBlurStyleSheets = QStringLiteral(
    "background-color: #aa000000;"
    "color: white;"
    "border: 1px solid royalblue;");

int main(int argc, char* argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);
  app.setApplicationName(QStringLiteral("Qt中文文档辅助工具"));
  app.setOrganizationName(QStringLiteral("QtDocumentCN"));
  app.setQuitOnLastWindowClosed(false);
  app.setWindowIcon(QIcon(QStringLiteral(":/icon/tools.ico")));

#ifdef Q_OS_WIN
  // https://forum.qt.io/topic/101391/windows-10-dark-theme/4
  QSettings reg(QStringLiteral("HKEY_CURRENT_"
                               "USER\\Software\\Microsoft\\Windows\\CurrentVers"
                               "ion\\Themes\\Personalize"),
                QSettings::NativeFormat);
  if (reg.value(QStringLiteral("AppsUseLightTheme")) == 0) {
    app.setStyle(QStyleFactory::create(QStringLiteral("Fusion")));
    QPalette darkPalette;
    QColor darkColor = QColor(43, 43, 43);
    QColor disabledColor = QColor(127, 127, 127);
    darkPalette.setColor(QPalette::Window, darkColor);
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(30, 30, 30));
    darkPalette.setColor(QPalette::AlternateBase, darkColor);
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
    darkPalette.setColor(QPalette::Button, darkColor);
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText,
                         disabledColor);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(0, 153, 188));
    darkPalette.setColor(QPalette::Highlight, QColor(65, 65, 65));
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText,
                         disabledColor);
    app.setPalette(darkPalette);
    app.setStyleSheet(QStringLiteral(
        "QMenu { border: 1px solid #a0a0a0; }"
        "QToolTip { color: #ffffff; background-color: #2a82da; border: 1px "
        "solid #a0a0a0; }"));
  }
#endif

  // Read shortcut from settings
  QSettings settings(QStringLiteral("config.ini"), QSettings::IniFormat);
  QString shortcut =
      settings.value(QStringLiteral("ShortCut"), QStringLiteral("Ctrl+Shift+C"))
          .toString();

  // Initialize tray icon
  QSystemTrayIcon tray;
  tray.setIcon(app.windowIcon());
  QMenu menu;

  // Initialize popup window
  SearchPopup search{nullptr, Qt::SplashScreen | Qt::FramelessWindowHint |
                                  Qt::WindowStaysOnTopHint};
  search.setStyleSheet(kFramelessBlurStyleSheets);

  // Initialize global hotkey
  QHotkey hotkey{QKeySequence{shortcut, QKeySequence::PortableText}};
  QObject::connect(&hotkey, &QHotkey::activated, &search, &SearchPopup::raise);

  // Reset hotkey
  auto ResetHotkey = [&shortcut, &tray, &hotkey](const QString& keys) -> bool {
    QString prev = shortcut;
    hotkey.setRegistered(false);
    hotkey.setShortcut(QKeySequence{keys, QKeySequence::PortableText});
    bool hotkeyRegistered = hotkey.isRegistered();
    if (hotkeyRegistered) {
      tray.showMessage(qApp->applicationName(),
                       QStringLiteral("快捷键 %1 已被占用！").arg(keys),
                       QSystemTrayIcon::Warning);
    } else {
      shortcut = keys;
      tray.showMessage(qApp->applicationName(),
                       QStringLiteral("快捷键已被设置为 %1 ").arg(keys),
                       QSystemTrayIcon::Information, 5000);
    }
    hotkey.setShortcut(shortcut, true);
    return !hotkeyRegistered;
  };

  // Action - index path
  QObject::connect(
      menu.addAction(QStringLiteral("索引路径...(&D)")), &QAction::triggered,
      [&settings, &tray, &search] {
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
            nullptr, QStringLiteral("索引路径"), dir);
        if (!d.isEmpty()) {
          QFileInfoList files;
          dir = d;
          settings.setValue(kDir, d);
          settings.sync();
          Traversal(files, d);
          QElapsedTimer timer;
          timer.start();
          size_t count = search.IndexFiles(files);
          tray.showMessage(
              qApp->applicationName(),
              QStringLiteral("完成索引，共 %1 个文件，%2 条标题，耗时 %3 ms")
                  .arg(files.count())
                  .arg(count)
                  .arg(timer.elapsed()),
              QSystemTrayIcon::Information, 5000);
        }
      });

  // Action - set shortcut
  QObject::connect(
      menu.addAction(QStringLiteral("设置快捷键(&S)")), &QAction::triggered,
      [&settings, &shortcut, &hotkey, &ResetHotkey] {
        auto input = new ShortcutInput(
            QKeySequence(shortcut, QKeySequence::PortableText), nullptr,
            Qt::SplashScreen | Qt::FramelessWindowHint |
                Qt::WindowStaysOnTopHint);

        QObject::connect(
            input, &ShortcutInput::finished,
            [&settings, &shortcut, &ResetHotkey, input](const QString& keys) {
              if (ResetHotkey(keys)) {
                shortcut = keys;
                settings.setValue(QStringLiteral("ShortCut"), shortcut);
                settings.sync();
              }
              QTimer::singleShot(250, input, SLOT(deleteLater()));
            });
        hotkey.setRegistered(false);
        input->setStyleSheet(kFramelessBlurStyleSheets +
                             QStringLiteral("padding: 5px; font: 28pt;"));
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
        }
        window->setOpacity(0.8);
      });

  // Action - homepage
  QObject::connect(
      menu.addAction(QStringLiteral("主页(&H)")), &QAction::triggered, [] {
        QDesktopServices::openUrl(
            QUrl{QStringLiteral("https://github.com/QtDocumentCN")});
      });

  // Action - exit
  QObject::connect(menu.addAction(QStringLiteral("退出(&Q)")),
                   &QAction::triggered, [] { qApp->exit(); });

  // Shot tray icon
  tray.setContextMenu(&menu);
  tray.show();
  ResetHotkey(shortcut);

  return app.exec();
}
