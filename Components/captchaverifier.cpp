#include "captchaverifier.h"

CaptchaVerifier::CaptchaVerifier(QWidget *parent)
    : QWidget{parent}
{
    QPixmap codeIcon(":/key.png");
    QPixmap changeIcon(":/refresh.png");
    QFile btnStyleFile(":/qss/PBS.qss");
    btnStyleFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString btnStyleString(btnStyleFile.readAll());
    btnStyleFile.close();
    layout = new QGridLayout(this);
    setLayout(layout);
    Ci = new CaptchaImage();
    textBox = new QLineEdit();
    changeCptcha = new QPushButton();
    changeCptcha->setText(tr("changeCaptcha"));
    changeCptcha->setIcon(QIcon(changeIcon));
    changeCptcha->setStyleSheet(btnStyleString);
    textBox->setStyleSheet("QLineEdit{padding: 5px;border: none;border-bottom: 1px solid blue;}"
                           "QLineEdit:focus{border-bottom-width: 2px;}");
    textBox->setClearButtonEnabled(true);
    textBox->addAction(QIcon(codeIcon),QLineEdit::LeadingPosition);
    textBox->setMaxLength(5);
    textBox->setPlaceholderText(tr("EnterDigitsCode: "));
    layout->addWidget(Ci,0,0,1,1,Qt::AlignHCenter);
    layout->addWidget(changeCptcha,0,1,1,1,Qt::AlignTrailing);
    layout->addWidget(textBox,1,0,1,2);

    QObject::connect(changeCptcha,&QPushButton::clicked,this,&CaptchaVerifier::on_changeCaptchaBtnClicked);
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


