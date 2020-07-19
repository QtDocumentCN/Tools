#ifndef QTDOCUMENTCN_TOOLS_INDEXLAUNCHER_H
#define QTDOCUMENTCN_TOOLS_INDEXLAUNCHER_H

#include <QtCore/QMultiMap>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QFileInfoList>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>

class Model;
class IndexLauncher : public QFrame {
  Q_OBJECT
 public:
  explicit IndexLauncher(QWidget* parent = nullptr, Qt::WindowFlags flags = {});

  size_t IndexFiles(const QFileInfoList& files);

  void raise();

 protected:
  bool eventFilter(QObject* object, QEvent* event) override;

 private:
  QLineEdit* input_;
  QListView* list_;
  Model* model_;
  QSortFilterProxyModel* filter_;
};

#endif  // QTDOCUMENTCN_TOOLS_INDEXLAUNCHER_H
