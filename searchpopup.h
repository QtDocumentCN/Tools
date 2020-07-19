#ifndef QTDOCUMENTCN_TOOLS_SEARCHPOPUP_H
#define QTDOCUMENTCN_TOOLS_SEARCHPOPUP_H

#include <QtCore/QMultiMap>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QStringList>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>

class Model;
class SearchPopup : public QFrame
{
 public:
  explicit SearchPopup(QWidget* parent = nullptr, Qt::WindowFlags flags = {});

  size_t IndexFiles(const QStringList& files);

  void raise();

 protected:
  virtual bool eventFilter(QObject* object, QEvent* event) override;

 private:
  QLineEdit* input_;
  QListView* list_;
  Model* model_;
  QSortFilterProxyModel* filter_;
};

#endif // QTDOCUMENTCN_TOOLS_SEARCHPOPUP_H
