#include "loginsignin.h"
#include "ui_loginsignin.h"
#include <utils/Util.h>
#include <QTabBar>

LoginSignIn::LoginSignIn(QWidget *parent,bool loginMode)
    : QWidget(parent)
    , ui(new Ui::LoginSignIn),isLogin(loginMode)
{
    ui->setupUi(this);
    enableStyle(ui->SignInBtn,"PBS.qss");
    ui->IconImageViewer->setPixmap(QPixmap(":/ico-cap-light.png"));
}

LoginSignIn::~LoginSignIn()
{
    delete ui;
}

void LoginSignIn::changeMethod(bool mode)
{
    isLogin = mode;
    changeMethod();
}

void LoginSignIn::changeMethod()
{
    if(isLogin){
        ui->changeMode->setText(tr("dontHaveAccount"));
        ui->SignInBtn->setText(tr("LoginText"));
        setWindowTitle(tr("LoginText"));
    }else{
        ui->changeMode->setText(tr("HaveAccount"));
        ui->SignInBtn->setText(tr("SignInText"));
        setWindowTitle(tr("SignInText"));
    }
    ui->captchaCode->reset();
}

void LoginSignIn::on_changeMode_clicked()
{
    isLogin = !isLogin;
    this->changeMethod();
}


void LoginSignIn::on_SignInBtn_clicked()
{
    qDebug() << "Clicked!";
}

