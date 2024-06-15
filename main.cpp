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
  auto translatorTemporary = util::installTranslator(&a);
  util::changeStyle(&a, util::Light);
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
  int id;
  int activationLevel;
  bool isLoggedIn = getActiveAccountUser(id, activationLevel);

  if (!isLoggedIn) {
    SplashScreen *splash = new SplashScreen();
    splash->show();
  } else {
    // make decision
    if (activationLevel == Added) {
      CodeVerifier *verifier = new CodeVerifier(id);
      verifier->show();
    } else if (activationLevel == Activated) {
      CompleteProfile *complete = new CompleteProfile(id);
      complete->show();
    } else {
      MainWindow *win = new MainWindow(id);
      win->show();
    }
  }

  int exec = a.exec();
  delete translatorTemporary;
  return exec;
}
