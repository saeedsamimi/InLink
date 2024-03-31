#ifndef LOGINSIGNIN_H
#define LOGINSIGNIN_H

#include <QWidget>
#include <QMainWindow>
#include <Pages/codeverifier.h>

namespace Ui {
class LoginSignIn;
}

class LoginSignIn : public QWidget
{
    Q_OBJECT

public:
    explicit LoginSignIn(bool loginMode = false,QWidget *parent = nullptr);
    ~LoginSignIn();

    void changeMethod(bool mode);
private slots:
    void on_changeMode_clicked();
    void on_SignInBtn_clicked();

private:
    Ui::LoginSignIn *ui;
    QMainWindow *referrer;
    CodeVerifier *verifier = nullptr;

    bool isLogin;

    void changeMethod();
    void doExit(const QString&,const QString&);
};

#endif // LOGINSIGNIN_H
