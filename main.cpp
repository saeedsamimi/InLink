#include <Pages/codeverifier.h>
#include <Pages/completeprofile.h>
#include <database/dbinit.h>
#include <database/user.h>
#include <utils/Util.h>
#include <utils/waitformorefeature.h>

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
  auto account = getActiveAccountUser();
  if (account == nullptr) {
    SplashScreen *splash = new SplashScreen();
    splash->show();
  } else {
    // make decision
    if (account->second == Added) {
      CodeVerifier *verifier = new CodeVerifier(account->first);
      verifier->show();
    } else if (account->second == Activated) {
      CompleteProfile *complete = new CompleteProfile(account->second);
      complete->show();
    } else {
      WaitForMoreFeature *dialog = new WaitForMoreFeature(account->first);
      dialog->show();
    }
  }
  int exec = a.exec();
  delete translatorTemporary;
  return exec;
}