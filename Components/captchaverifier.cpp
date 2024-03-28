#include "captchaverifier.h"
#include <utils/Util.h>

CaptchaVerifier::CaptchaVerifier(QWidget *parent)
    : QWidget{parent}
{
    setupUi();
}

CaptchaVerifier::~CaptchaVerifier()
{
    delete changeCptcha;
    delete Ci;
    delete layout;
    delete textBox;
}

void CaptchaVerifier::on_changeCaptchaBtnClicked()
{
    Ci->updateCaptcha();
    textBox->clear();
}

void CaptchaVerifier::setupUi()
{
    QPixmap codeIcon(":/key.png");
    QPixmap changeIcon(":/refresh.png");
    layout = new QGridLayout(this);
    setLayout(layout);
    Ci = new CaptchaImage();
    textBox = new QLineEdit();
    changeCptcha = new QPushButton();
    changeCptcha->setText(tr("changeCaptcha"));
    changeCptcha->setIcon(QIcon(changeIcon));
    enableStyle(this,"PBS.qss");
    enableStyle(textBox,"CVTBS.qss");
    textBox->setClearButtonEnabled(true);
    textBox->addAction(QIcon(codeIcon),QLineEdit::LeadingPosition);
    textBox->setMaxLength(5);
    textBox->setPlaceholderText(tr("EnterDigitsCode: "));
    layout->addWidget(Ci,0,0,1,1,Qt::AlignHCenter);
    layout->addWidget(changeCptcha,0,1,1,1,Qt::AlignTrailing);
    layout->addWidget(textBox,1,0,1,2);

    QObject::connect(changeCptcha,&QPushButton::clicked,this,&CaptchaVerifier::on_changeCaptchaBtnClicked);
}


