#ifndef LOGINSIGNIN_H
#define LOGINSIGNIN_H

#include <QWidget>

namespace Ui {
class LoginSignIn;
}

class LoginSignIn : public QWidget
{
    Q_OBJECT

public:
    explicit LoginSignIn(QWidget *parent = nullptr);
    ~LoginSignIn();

private:
    Ui::LoginSignIn *ui;
};

#endif // LOGINSIGNIN_H
