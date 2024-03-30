#ifndef LOGINSIGNIN_H
#define LOGINSIGNIN_H

#include <QWidget>
#include <QMainWindow>
#include <db/db_config.h>

namespace Ui {
class LoginSignIn;
}

class LoginSignIn : public QWidget
{
    Q_OBJECT

public:
    explicit LoginSignIn(db::db_config *config,QWidget *parent = nullptr,bool loginMode = false);
    ~LoginSignIn();

    void changeMethod(bool mode);
private slots:
    void on_changeMode_clicked();
    void on_SignInBtn_clicked();

private:
    Ui::LoginSignIn *ui;
    QMainWindow *referrer;
    bool isLogin;
    db::db_config *config;

    void changeMethod();
};

#endif // LOGINSIGNIN_H
