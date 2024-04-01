#include "splashscreen.h"
#include "loginsignin.h"
#include "test/test_captcha.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <utils/Util.h>
#include <database/dbinit.h>
#include <database/user.h>
#include <Pages/codeverifier.h>
#include <Pages/completeprofile.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPalette pal = a.palette();
    pal.setColor(QPalette::Window, Qt::white);
    a.setPalette(pal);
    auto translatorTemporary = installTranslator(&a);
    initDB();
    auto accounts = getActiveAccountUser();
    if(accounts.empty()){
        SplashScreen *splash = new SplashScreen();
        splash->show();
    }else{
        qDebug() << accounts;
    }
    CompleteProfile CP(0);
    CP.show();
    int exec = a.exec();
    delete translatorTemporary;
    return exec;
}
