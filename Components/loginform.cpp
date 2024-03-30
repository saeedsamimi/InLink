#include "loginform.h"
#include "ui_loginform.h"
#include <utils/Util.h>
#include <string>

LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginForm) , hideLogo(":/hide.png"), showLogo(":/eye.png")
{
    ui->setupUi(this);
    enableStyle(this,"LS.qss");
    ui->userNameEdit->addAction(QIcon(QPixmap(":/businessman.png")),QLineEdit::LeadingPosition);
    ui->passwordEdit->addAction(QIcon(QPixmap(":/padlock.png")),QLineEdit::LeadingPosition);
    eyeAction = ui->passwordEdit->addAction(QIcon(showLogo),QLineEdit::TrailingPosition);
    eyeAction->setCheckable(true);
    QObject::connect(eyeAction,&QAction::triggered,this,&LoginForm::passwordVisibilityChanged);
}

LoginForm::~LoginForm()
{
    delete ui;
}

QPair<QString,QString> LoginForm::getUser() const
{
    return {ui->userNameEdit->text(),ui->passwordEdit->text()};
}

void LoginForm::passwordVisibilityChanged()
{
    if(eyeAction->isChecked()){
        ui->passwordEdit->setEchoMode(QLineEdit::Normal);
        eyeAction->setIcon(hideLogo);
    }else{
        ui->passwordEdit->setEchoMode(QLineEdit::Password);
        eyeAction->setIcon(showLogo);
    }
}
