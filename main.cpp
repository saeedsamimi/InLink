#include "mainwindow.h"
#include "loginsignin.h"
#include "test/test_captcha.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <db_config.h>
#include <mongocxx/instance.hpp>

using db::db_config;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    Q_UNUSED(translator.load("InLink_en_US"));
    a.installTranslator(&translator);
    db_config config("testDB");
    MainWindow w;
    LoginSignIn page;
    page.show();
    w.show();
    return a.exec();
}
