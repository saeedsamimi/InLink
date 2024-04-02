#include "codeverifyedit.h"

#include <QKeyEvent>

CodeVerifyEdit::CodeVerifyEdit(QWidget *parent) : QLineEdit(parent) {
  setFixedSize(100, 100);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  setMaxLength(1);
  setAlignment(Qt::AlignCenter);
  setFont(QFont("Arial", 18, 800));
}

void CodeVerifyEdit::setIndex(uchar _index) { index = _index; }

uchar CodeVerifyEdit::getIndex() { return index; }

void CodeVerifyEdit::keyPressEvent(QKeyEvent *event) {
  if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9 ||
      event->key() == Qt::Key_Backspace) {
    if (text().isEmpty() && event->key() == Qt::Key_Backspace)
      emit cleared(index);
    else if (text().isEmpty())
      emit filled(index);
    else if (event->key() != Qt::Key_Backspace)
      emit filled(index);

    bool bef = text().isEmpty();
    QLineEdit::keyPressEvent(event);
    if (index == 3 && !text().isEmpty() && bef) emit filled(4);
  }
}
