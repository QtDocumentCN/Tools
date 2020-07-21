#ifndef QTDOCUMENTCN_TOOLS_INDEXLAUNCHER_H
#define QTDOCUMENTCN_TOOLS_INDEXLAUNCHER_H

#include <QtCore/QFileInfoList>
#include <QtWidgets/QFrame>

class IndexLauncherPrivate;
class IndexLauncher : public QFrame {
  Q_OBJECT
  Q_DECLARE_PRIVATE(IndexLauncher)

 public:
  explicit IndexLauncher(QWidget* parent = nullptr, Qt::WindowFlags flags = {});

  size_t IndexFiles(const QFileInfoList& files);

  void Trigger();

 protected:
  bool eventFilter(QObject* object, QEvent* event) override;
};

#endif  // QTDOCUMENTCN_TOOLS_INDEXLAUNCHER_H
