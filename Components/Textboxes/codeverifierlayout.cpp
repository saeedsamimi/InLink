#include "codeverifierlayout.h"

#include <utils/Util.h>

#include <QRegularExpressionValidator>

// connect to acronym!
#define CTA(x, y)                                                              \
  connect(&boxes[i], &CodeVerifyEdit::x, this, &CodeVerifierLayout::y)

CodeVerifierLayout::CodeVerifierLayout(QWidget *parent)
    : QWidget{parent}, boxes{}, layout(), dialog(this) {
  setupUI();
  dialog.show();
}

QString CodeVerifierLayout::getText() {
  QString temp("");
  for (auto &box : boxes)
    temp.append(box.text());
  return temp;
}

void CodeVerifierLayout::onBoxFilled(uchar i) {
  if (i < 4) {
    int j;
    for (j = i + 1; j < 4 && !boxes[j].text().isEmpty(); j++)
      ;
    if (j < 4)
      boxes[j].setFocus();
  } else {
    const QString &temp = getText();
    if (temp.length() == 4) {
      if (dialog.validate(temp))
        emit onAccepted();
      else {
        if (dialog.isHidden())
          dialog.show();
        dialog.randomize();
      }
    }
  }
}

void CodeVerifierLayout::onBoxCleared(uchar i) {
  int j;
  for (j = i - 1; j >= 0 && boxes[j].text().isEmpty(); j--)
    ;
  boxes[std::max(0, j)].setFocus();
}

CodeVerifierLayout::~CodeVerifierLayout() = default;

void CodeVerifierLayout::setupUI() {
  for (uchar i = 0; i < 4; i++) {
    boxes[i].setIndex(i);
    CTA(filled, onBoxFilled);
    CTA(cleared, onBoxCleared);
    layout.addWidget(boxes + i);
  }
  setLayout(&layout);
  util::enableStyle(this, "CVS.qss");
}
