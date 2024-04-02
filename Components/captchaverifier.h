#ifndef CAPTCHAVERIFIER_H
#define CAPTCHAVERIFIER_H

#include <QIODevice>
#include <QObject>
#include <QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

#include "captchaimage.h"

class CaptchaVerifier : public QWidget {
  Q_OBJECT
 public:
  explicit CaptchaVerifier(QWidget *parent = nullptr);

  ~CaptchaVerifier();

  bool isValidated();
  void reset();
  bool Hint();
 protected slots:
  void on_updateCaptcha_clicked();
  void on_captchaVerify_triggered();

 private:
  QGridLayout *layout;
  CaptchaImage *Ci;
  QLabel *msg;
  QLineEdit *textBox;
  QAction *captchaVerify;
  QPushButton *changeCptcha;
  bool isValid;

  void setupUi();
  void setError(const QString &);
  void setWarning(const QString &);
  void setSuccess(const QString &);
  void statusUtil(const QString &, QColor color);
};

#endif  // CAPTCHAVERIFIER_H
