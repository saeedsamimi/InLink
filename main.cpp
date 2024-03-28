#include "mainwindow.h"
#include "loginsignin.h"
#include "test/test_captcha.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <db_config.h>
#include <utils/Util.h>
#include <mongocxx/instance.hpp>

using db::db_config;

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
