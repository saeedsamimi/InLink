#include "captchaverifier.h"

#include <utils/Util.h>

CaptchaVerifier::CaptchaVerifier(QWidget *parent)
    : QWidget{parent}, isValid(false) {
  setupUi();
}

CaptchaVerifier::~CaptchaVerifier() {
  delete changeCptcha;
  delete Ci;
  delete layout;
  delete textBox;
}

bool CaptchaVerifier::isValidated() { return isValid; }

void CaptchaVerifier::reset() {
  isValid = false;
  setEnabled(true);
  Ci->setEnabled(true);
  textBox->clear();
  Ci->updateCaptcha();
  msg->clear();
}

bool CaptchaVerifier::Hint() {
  on_captchaVerify_triggered();
  return isValid;
}

void CaptchaVerifier::on_updateCaptcha_clicked() {
  Ci->updateCaptcha();
  textBox->clear();
}

void CaptchaVerifier::on_captchaVerify_triggered() {
  if (textBox->text().isEmpty()) {
    setWarning(tr("fillCaptcha"));
  } else {
    if (Ci->validate(textBox->text())) {
      setEnabled(false);
      Ci->setEnabled(false);
      isValid = true;
      setSuccess(tr("captchValidatedSuccess"));
    } else {
      on_updateCaptcha_clicked();
      isValid = false;
      setError(tr("incorrectCaptcha"));
    }
  }
}

void CaptchaVerifier::setupUi() {
  QPixmap codeIcon(":/key.png");
  QPixmap changeIcon(":/refresh.png");
  layout = new QGridLayout(this);
  setLayout(layout);
  Ci = new CaptchaImage();
  textBox = new QLineEdit();
  msg = new QLabel();
  msg->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
  captchaVerify = textBox->addAction(QIcon(QPixmap(":/check.png")),
                                     QLineEdit::TrailingPosition);
  captchaVerify->setObjectName("captchaVerify");
  changeCptcha = new QPushButton();
  changeCptcha->setObjectName("updateCaptcha");
  changeCptcha->setText(tr("changeCaptcha"));
  changeCptcha->setIcon(QIcon(changeIcon));
  enableStyle(this, "PBS.qss");
  enableStyle(textBox, "CVTBS.qss");
  textBox->setClearButtonEnabled(true);
  textBox->addAction(QIcon(codeIcon), QLineEdit::LeadingPosition);
  textBox->setMaxLength(5);
  textBox->setPlaceholderText(tr("EnterDigitsCode: "));
  layout->addWidget(Ci, 0, 0, 1, 1, Qt::AlignHCenter);
  layout->addWidget(changeCptcha, 0, 1, 1, 1, Qt::AlignTrailing);
  layout->addWidget(textBox, 1, 0, 1, 2);
  layout->addWidget(msg, 2, 0, 1, 2, Qt::AlignLeading);

  QMetaObject::connectSlotsByName(this);
}

void CaptchaVerifier::setError(const QString &error) {
  statusUtil(error, Qt::red);
}

void CaptchaVerifier::setWarning(const QString &warn) {
  statusUtil(warn, Qt::blue);
}

void CaptchaVerifier::setSuccess(const QString &_msg) {
  statusUtil(_msg, Qt::green);
}

void CaptchaVerifier::statusUtil(const QString &text, QColor color) {
  QPalette pal = msg->palette();
  pal.setColor(QPalette::WindowText, color);
  msg->setPalette(pal);
  msg->setText(text);
}
