#include "iconbadges.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>

IconBadges::IconBadges(QWidget *parent) : QWidget(parent), counter(0) {}

void IconBadges::setIcon(int index, const QPixmap &icon) {
  Q_ASSERT(index >= 0 && index < 3);
  icons[index] = utilTransform(icon);
  update();
}

unsigned int IconBadges::counterValue() const { return counter; }

void IconBadges::setCounterValue(unsigned int new_value) {
  counter = new_value;
  update();
  emit counterValueChanged(new_value);
}

void IconBadges::increaseValue(unsigned int d) { setCounterValue(counter + d); }

void IconBadges::decreaseValue(unsigned int d) { setCounterValue(counter - d); }

void IconBadges::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  qreal r = 14;
  qreal offset = 4 * r / 5;
  QBrush fillingBrush = palette().accent();
  if (fillingBrush.color().blackF() < 0.5) {
    fillingBrush.setColor(QColor(40, 40, 40));
  } else {
    fillingBrush.setColor(QColor(200, 200, 200));
  }
  painter.setBrush(fillingBrush);
  painter.setPen(palette().window().color());
  qreal max = 0;
  for (int i = 0; i < 3; i++) {
    max = ((2 * i) * offset) / 2 + r;
    QPainterPath path;
    path.addEllipse(QPointF(max + 2, r + 1), r, r);
    painter.setClipPath(path);
    painter.drawEllipse(QPointF(max + 2, r + 1), r, r);
    if (!icons[2 - i].isNull())
      painter.drawPixmap(QPointF(max - r + 2, 1), icons[2 - i]);
    max += r;
  }
  painter.setClipRect(rect());
  painter.setBrush(QColorConstants::Transparent);
  painter.setPen(palette().windowText().color());
  if (underMouse()) {
    QFont current_font = font();
    current_font.setBold(true);
    painter.setFont(current_font);
  }
  painter.drawText(QPointF(max + 5, r - 3 + fontMetrics().height() / 2),
                   QString("%1 Likes").arg(counter));
}

void IconBadges::enterEvent(QEnterEvent *event) {
  QWidget::enterEvent(event);
  update();
}

void IconBadges::leaveEvent(QEvent *event) {
  QWidget::leaveEvent(event);
  update();
}

void IconBadges::mouseDoubleClickEvent(QMouseEvent *event) {
  if (event->buttons() | Qt::LeftButton && isEnabled())
    emit clicked();
}

QPixmap IconBadges::utilTransform(const QPixmap &pic) {
  return pic.isNull() ? pic
                      : pic.scaled(38, 38, Qt::KeepAspectRatio,
                                   Qt::SmoothTransformation);
}
