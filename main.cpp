#include <Pages/codeverifier.h>
#include <Pages/completeprofile.h>
#include <database/dbinit.h>
#include <database/user.h>
#include <utils/Util.h>

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "loginsignin.h"
#include "splashscreen.h"
#include "test/test_captcha.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QPalette pal = a.palette();
  pal.setColor(QPalette::Window, Qt::white);
  a.setPalette(pal);
  auto translatorTemporary = installTranslator(&a);
  initDB();
  auto accounts = getActiveAccountUser();
  if (accounts.empty()) {
    SplashScreen *splash = new SplashScreen();
    splash->show();
  } else {
    qDebug() << accounts;
  }
  CompleteProfile CP(1);
  CP.show();
  int exec = a.exec();
  delete translatorTemporary;
  return exec;
}
