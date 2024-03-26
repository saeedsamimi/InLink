#include "captchaimage.h"

CaptchaImage::CaptchaImage(QWidget *parent)
    : QGraphicsView{parent}
{
    setScene(new QGraphicsScene());
    ch.randomize();
    ch.setDifficulty(3);
    ch.setFont(QFont("Arial",25));
    ch.generateText();
    setStyleSheet("background: transparent; border: none;");
    qDebug() << "The text is: " << (currText = ch.captchaText());
    pixmapItem = scene()->addPixmap(QPixmap::fromImage(ch.captchaImage()));
}

void CaptchaImage::resizeEvent(QResizeEvent *event)
{
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

bool CaptchaImage::validate(const QString &text)
{
    return QString::compare(currText,text,Qt::CaseInsensitive);
}
