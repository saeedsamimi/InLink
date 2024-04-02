#ifndef TEST_CAPTCHA_H
#define TEST_CAPTCHA_H

#include <Components/captcha.h>

#include <QDialog>
#include <QPaintEvent>
#include <QPainter>

namespace Ui {
class test_captcha;
}

class test_captcha : public QDialog {
  Q_OBJECT

 public:
  explicit test_captcha(QWidget *parent = nullptr);
  ~test_captcha();

 private:
  Ui::test_captcha *ui;

 protected:
  virtual void paintEvent(QPaintEvent *);
};

#endif  // TEST_CAPTCHA_H
