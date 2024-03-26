#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginForm) , showText(tr("ShowPasswordText")) , hideText(tr("HidePasswordText"))
{
    QPixmap businessLogo(":/businessman.png");
    QPixmap padlockLogo(":/padlock.png");
    ui->setupUi(this);
    ui->userNameEdit->addAction(QIcon(businessLogo),QLineEdit::LeadingPosition);
    ui->passwordEdit->addAction(QIcon(padlockLogo),QLineEdit::LeadingPosition);
    ui->PasswordVisibility->setText(showText);
    QObject::connect(ui->PasswordVisibility,&QCheckBox::stateChanged,this,&LoginForm::passwordVisibilityChanged);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::passwordVisibilityChanged()
{
    if(ui->PasswordVisibility->checkState() == Qt::Checked){
        ui->passwordEdit->setEchoMode(QLineEdit::Normal);
        ui->PasswordVisibility->setText(hideText);
    }else{
        ui->passwordEdit->setEchoMode(QLineEdit::Password);
        ui->PasswordVisibility->setText(showText);
    }
}
