#ifndef CAPTCHAIMAGE_H
#define CAPTCHAIMAGE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QResizeEvent>
#include <QWidget>

#include "captcha.h"

class CaptchaImage : public QGraphicsView {
  Q_OBJECT
 public:
  explicit CaptchaImage(QWidget *parent = nullptr);

  void resizeEvent(QResizeEvent *event);
  bool validate(const QString &text);
  void updateCaptcha();
  void setEnabled(bool);
 signals:

 private:
  Captcha ch;
  QGraphicsPixmapItem *pixmapItem;
  QString currText;
};

#endif  // CAPTCHAIMAGE_H
