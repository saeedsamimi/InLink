#ifndef CAPTCHAIMAGE_H
#define CAPTCHAIMAGE_H

#include "captcha.h"
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QResizeEvent>

class CaptchaImage : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CaptchaImage(QWidget *parent = nullptr);

    void resizeEvent(QResizeEvent *event);
    bool validate(const QString & text);
    void updateCaptcha();
    void setEnabled(bool);
signals:

private:
    Captcha ch;
    QGraphicsPixmapItem *pixmapItem;
    QString currText;
};

#endif // CAPTCHAIMAGE_H
