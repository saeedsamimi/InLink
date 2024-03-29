#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPropertyAnimation>
#include <loginsignin.h>
#include <db/db_config.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(db::db_config *,QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_SignInBtn_clicked();
private:
    Ui::MainWindow *ui;
    QLabel *FindCourceLbl;
    LoginSignIn *loginPage;
    db::db_config *config;
};
#endif // MAINWINDOW_H
