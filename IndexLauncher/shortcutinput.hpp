#ifndef QTDOCUMENTCN_TOOLS_SHORTCUTINPUT_HPP
#define QTDOCUMENTCN_TOOLS_SHORTCUTINPUT_HPP

#include <Qt>
#include <QtGui/QFont>
#include <QtGui/QKeySequence>
#include <QtGui/QFocusEvent>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QLabel>

class ShortcutInput : public QLabel {
  Q_OBJECT
 public:
  ShortcutInput(QWidget* parent = nullptr, Qt::WindowFlags flags = {})
      : ShortcutInput(QKeySequence{}, parent, flags) {}

  ShortcutInput(QKeySequence sequence, QWidget* parent = nullptr,
                Qt::WindowFlags flags = {})
      : QLabel(parent, flags), sequence_(sequence) {
    display();
  }

  QKeySequence sequence() const {
    if ((modifiers_ == Qt::NoModifier) && (key_ == 0)) {
      return sequence_;
    } else {
      return QKeySequence(modifiers_ + key_);
    }
  }

  Q_SIGNAL void finished(const QString& keys = {});

 protected:
  virtual void keyPressEvent(QKeyEvent* event) override {
    modifiers_ |= event->modifiers();
    int key = event->key();
    if ((key == 0) || (key == Qt::Key_unknown)) {
      key_ = 0;
    } else if (key == Qt::Key_Escape) {
      emit finished(sequence_.toString(QKeySequence::PortableText));
    } else if ((key >= Qt::Key_A) && (key <= Qt::Key_Z)) {
      key_ = key;
    }
    display();
  }

  virtual void keyReleaseEvent(QKeyEvent* event) override {
    if (key_ != 0) {
      emit finished(sequence().toString(QKeySequence::PortableText));
    } else {
      switch (event->key()) {
        case Qt::Key_Shift:
          modifiers_ ^= Qt::ShiftModifier;
          break;
        case Qt::Key_Control:
          modifiers_ ^= Qt::ControlModifier;
          break;
        case Qt::Key_Meta:
          modifiers_ ^= Qt::MetaModifier;
          break;
        case Qt::Key_Alt:
          modifiers_ ^= Qt::AltModifier;
          break;
        default:
          break;
      }
    }
    display();
  }

  virtual void focusOutEvent(QFocusEvent* event) override {
    if (event->lostFocus())  {
      emit finished(sequence().toString(QKeySequence::PortableText));
    }
  }

 private:
  void display() {
    if (sequence_.isEmpty() && (modifiers_ == Qt::NoModifier) && (key_ != 0)) {
      setText(tr("Press any shortcut"));
    } else {
      setText(sequence().toString(QKeySequence::PortableText));
    }
    resize(sizeHint());
  }

  QKeySequence sequence_;
  Qt::KeyboardModifiers modifiers_ = Qt::NoModifier;
  int key_ = 0;
};

#endif // QTDOCUMENTCN_TOOLS_SHORTCUTINPUT_HPP
