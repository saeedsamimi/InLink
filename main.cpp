#include "mainwindow.h"
#include "loginsignin.h"
#include "test/test_captcha.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <utils/Util.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto translatorTemporary = installTranslator(&a);
    MainWindow w;
    w.show();
    int exec = a.exec();
    delete translatorTemporary;
    return exec;
}
