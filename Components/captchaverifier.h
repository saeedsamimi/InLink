#ifndef CAPTCHAVERIFIER_H
#define CAPTCHAVERIFIER_H

#include <QObject>
#include <QWidget>
#include "captchaimage.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QIODevice>

class CaptchaVerifier : public QWidget
{
    Q_OBJECT
public:
    explicit CaptchaVerifier(QWidget *parent = nullptr);

    ~CaptchaVerifier();
protected slots:
    void on_changeCaptchaBtnClicked();
private:
    QGridLayout *layout;
    CaptchaImage *Ci;
    QLineEdit *textBox;
    QPushButton *changeCptcha;
};

#endif // CAPTCHAVERIFIER_H
