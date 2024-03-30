#include "loginform.h"
#include "ui_loginform.h"
#include <utils/Util.h>
#include <string>

LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginForm) , hideLogo(":/hide.png"), showLogo(":/eye.png")
{
    ui->setupUi(this);
    userValidator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z0-9]+"));
    ui->userNameEdit->setValidator(userValidator);
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
    delete userValidator;
}

QPair<QString,QString> LoginForm::getUser() const
{
    static QRegularExpression re("(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{8,}");
    auto passText = ui->passwordEdit->text();
    auto usrText = ui->userNameEdit->text();
    if(re.match(passText).hasMatch()){
        if(usrText.length() > 2)
            return {ui->userNameEdit->text(),passText};
        throw QObject::tr("the username must be at least 2 characters!");
    }
    throw QObject::tr("the password must be at least 8 characters and must have letters and numbers!");
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
