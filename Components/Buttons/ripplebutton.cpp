#include "ripplebutton.h"
#include <QPainterPath>
#include <QStyleOptionButton>

RippleButton::RippleButton(QWidget *parent)
    : QPushButton(parent), m_ripple_radius(0),
      m_animation(new QPropertyAnimation(this, "rippleRadius")) {
  m_animation->setDuration(300);
  m_animation->setStartValue(0);
  m_animation->setEndValue(std::max(width(), height()));
  m_animation->setEasingCurve(QEasingCurve::InSine);
  connect(m_animation, &QPropertyAnimation::finished, this,
          &RippleButton::onRippleFinished);
}

qreal RippleButton::rippleRadius() const { return m_ripple_radius; }

void RippleButton::setRippleRadius(qreal radius) {
  m_ripple_radius = radius;
  update();
}

void RippleButton::paintEvent(QPaintEvent *e) {
  QPushButton::paintEvent(e);
  QPainter painter(this);
  QPainterPath path;
  auto m_rect = rect().marginsRemoved(QMargins(2, 2, 2, 2));
  path.addRoundedRect(m_rect, 10, 10);
  painter.setClipPath(path);
  if (m_ripple_radius > 0) {
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 25));
    painter.drawEllipse(m_click_position, m_ripple_radius, m_ripple_radius);
  }
  if (isChecked()) {
    painter.setPen(QPen(palette().accent().color(), 6));
    painter.drawLine(m_rect.bottomLeft(), m_rect.bottomRight());
  }
}

void RippleButton::mousePressEvent(QMouseEvent *e) {
  QPushButton::mousePressEvent(e);
  if (e->buttons() & (Qt::LeftButton | Qt::RightButton)) {
    m_click_position = e->pos();
    m_animation->stop();
    m_animation->start();
  }
}

void RippleButton::resizeEvent(QResizeEvent *event) {
  QPushButton::resizeEvent(event);
  m_animation->setEndValue(std::max(width(), height()));
}

void RippleButton::onRippleFinished() {
  QTimer::singleShot(250, this, [this]() {
    if (!underMouse())
      setRippleRadius(0);
  });
}
