#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPropertyAnimation>
#include <loginsignin.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_SignInBtn_clicked();
private:
    Ui::MainWindow *ui;
    QLabel *FindCourceLbl;
    LoginSignIn *loginPage;
};
#endif // MAINWINDOW_H
