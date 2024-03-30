#ifndef CAPTCHAVERIFIER_H
#define CAPTCHAVERIFIER_H

#include <QObject>
#include <QWidget>
#include "captchaimage.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QIODevice>

class CaptchaVerifier : public QWidget
{
    Q_OBJECT
public:
    explicit CaptchaVerifier(QWidget *parent = nullptr);

    ~CaptchaVerifier();

    bool isValidated();
    void reset();
    bool Hint();
protected slots:
    void on_updateCaptcha_clicked();
    void on_captchaVerify_triggered();
private:
    QGridLayout *layout;
    CaptchaImage *Ci;
    QLabel *msg;
    QLineEdit *textBox;
    QAction *captchaVerify;
    QPushButton *changeCptcha;
    bool isValid;

    void setupUi();
    void setError(const QString &);
    void setWarning(const QString &);
    void setSuccess(const QString &);
    void statusUtil(const QString &,QColor color);
};

#endif // CAPTCHAVERIFIER_H
