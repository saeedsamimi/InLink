#ifndef LOGINSIGNIN_H
#define LOGINSIGNIN_H

#include <QWidget>
#include <QMainWindow>

namespace Ui {
class LoginSignIn;
}

class LoginSignIn : public QWidget
{
    Q_OBJECT

public:
    explicit LoginSignIn(QWidget *parent = nullptr,bool loginMode = false);
    ~LoginSignIn();
private slots:
    void on_changeMode_clicked();
private:
    Ui::LoginSignIn *ui;
    QMainWindow *referrer;
    bool isLogin;

    void changeMethod();
};

#endif // LOGINSIGNIN_H
