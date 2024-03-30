#include "captchaimage.h"

CaptchaImage::CaptchaImage(QWidget *parent)
    : QGraphicsView{parent}
{
    setScene(new QGraphicsScene());
    scene()->setBackgroundBrush(QBrush(QGradient(QGradient::CloudyApple)));
    ch.randomize();
    ch.setDifficulty(3);
    ch.setFont(QFont("Arial",25));
    ch.generateText();
    setStyleSheet("background: transparent; border: none;");
    pixmapItem = scene()->addPixmap(QPixmap::fromImage(ch.captchaImage()));
}

void CaptchaImage::resizeEvent(QResizeEvent *event)
{
    if(isEnabled())
        fitInView(pixmapItem,Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}

void CaptchaImage::updateCaptcha(){
    ch.randomize();
    ch.generateText();
    scene()->removeItem(pixmapItem);
    currText = ch.captchaText();
    pixmapItem = scene()->addPixmap(QPixmap::fromImage(ch.captchaImage()));
}

void CaptchaImage::setEnabled(bool _enabled)
{
    if(_enabled)
        pixmapItem = scene()->addPixmap(QPixmap::fromImage(ch.captchaImage()));
    else{
        scene()->removeItem(pixmapItem);
        pixmapItem = nullptr; //prevent from null pointers exceptions
        scene()->clear();
    }
    QGraphicsView::setEnabled(_enabled);
}

bool CaptchaImage::validate(const QString &text)
{
    return !QString::compare(currText,text,Qt::CaseInsensitive);
}
