#include "loginsignin.h"

#include <database/user.h>
#include <utils/Util.h>

#include <QMessageBox>
#include <QTabBar>

#include "ui_loginsignin.h"

LoginSignIn::LoginSignIn(bool loginMode, QWidget *parent)
    : QWidget(parent), ui(new Ui::LoginSignIn), isLogin(loginMode) {
  ui->setupUi(this);
  changeMethod();
  enableStyle(ui->SignInBtn, "PBS.qss");
  ui->IconImageViewer->setPixmap(QPixmap(":/ico-cap-light.png"));
}

LoginSignIn::~LoginSignIn() { delete ui; }

void LoginSignIn::changeMethod(bool mode) {
  isLogin = mode;
  changeMethod();
}

void LoginSignIn::changeMethod() {
  if (isLogin) {
    ui->changeMode->setText(tr("dontHaveAccount"));
    ui->SignInBtn->setText(tr("LoginText"));
    setWindowTitle(tr("LoginText"));
  } else {
    ui->changeMode->setText(tr("HaveAccount"));
    ui->SignInBtn->setText(tr("SignInText"));
    setWindowTitle(tr("SignInText"));
  }
  ui->captchaCode->reset();
}

void LoginSignIn::doExit(const QString &username, const QString &password) {
  int ID = addAccount(username);
  verifier = new CodeVerifier(ID);
  verifier->show();
  close();
}

void LoginSignIn::on_changeMode_clicked() {
  isLogin = !isLogin;
  this->changeMethod();
}

void LoginSignIn::on_SignInBtn_clicked() {
  QPair<QString, QString> res;
  try {
    res = ui->widget->getUser();
  } catch (QString &e) {
    QMessageBox::critical(this, "Error", e, QMessageBox::Ok);
    return;
  }
  if (!ui->captchaCode->isValidated() && !ui->captchaCode->Hint()) return;
  if (isLogin) {
    try {
      validateUser(res.first, res.second);
      QMessageBox::information(this, "Success",
                               QObject::tr("You are logged in successfully!"),
                               QMessageBox::Ok);
      doExit(res.first, res.second);
    } catch (QPair<QString, bool> &err) {
      if (err.second) {
        int res = QMessageBox::critical(this, "Error", err.first,
                                        QMessageBox::Ok, QMessageBox::Cancel);
        if (res == QMessageBox::Ok) changeMethod(!isLogin);
      } else
        QMessageBox::critical(this, "Error", err.first, QMessageBox::Ok);
    } catch (QSqlError &err) {
      QMessageBox::critical(this, "Unexpected Error",
                            err.databaseText().append(". Please try again!"),
                            QMessageBox::Ok);
    }
  } else {
    try {
      insertUser(res.first, res.second);
      QMessageBox::information(this, "Success",
                               QObject::tr("You are Signed in successfully!"),
                               QMessageBox::Ok);
      doExit(res.first, res.second);
    } catch (QString &err) {
      int res = QMessageBox::critical(this, "Error", err, QMessageBox::Ok,
                                      QMessageBox::Cancel);
      if (res == QMessageBox::Ok) changeMethod(!isLogin);
    } catch (QSqlError &err) {
      QMessageBox::critical(this, "Unexpected Error",
                            err.databaseText().append("Please try again!"),
                            QMessageBox::Ok);
    }
  }
}
