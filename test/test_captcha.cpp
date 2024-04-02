#include "test_captcha.h"

#include "ui_test_captcha.h"

test_captcha::test_captcha(QWidget *parent)
    : QDialog(parent), ui(new Ui::test_captcha) {
  ui->setupUi(this);
}

test_captcha::~test_captcha() { delete ui; }

void test_captcha::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  Captcha cp;
  cp.randomize();
  cp.setDifficulty(3);
  cp.generateText();
  painter.drawImage(30, 30, cp.captchaImage());
}
