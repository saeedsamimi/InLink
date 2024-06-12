#include <Pages/codeverifier.h>
#include <Pages/completeprofile.h>
#include <Pages/mainwindow.h>
#include <database/dbinit.h>
#include <database/user.h>
#include <utils/Util.h>
#include <utils/waitformorefeature.h>

#include <QApplication>
#include <QLocale>
#include <QMessageBox>
#include <QTranslator>

#include "loginsignin.h"
#include "splashscreen.h"
#include "test/test_captcha.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QPalette pal = a.palette();
  pal.setColor(QPalette::Window, Qt::white);
  a.setPalette(pal);
  auto translatorTemporary = util::installTranslator(&a);
  try {
    initDB();
  } catch (QSqlError &err) {
    QMessageBox::critical(
        nullptr, "connection failed",
        QString("Could not connect to the database because: %1")
            .arg(err.text()));
    a.exit(0);
    exit(0);
  }
  auto account = getActiveAccountUser();
  try {
    if (account == nullptr) {
      SplashScreen *splash = new SplashScreen();
      splash->show();
    } else {
      // make decision
      if (account->second == Added) {
        CodeVerifier *verifier = new CodeVerifier(account->first);
        verifier->show();
      } else if (account->second == Activated) {
        CompleteProfile *complete = new CompleteProfile(account->first);
        complete->show();
      } else {
        MainWindow *win = new MainWindow(account->first);
        win->show();
      }
    }
  } catch (QSqlError &err) {
    qDebug() << err.text();
  }

  int exec = a.exec();
  delete translatorTemporary;
  return exec;
}
