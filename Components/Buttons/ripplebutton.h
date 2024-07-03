#ifndef RIPPLEBUTTON_H
#define RIPPLEBUTTON_H

#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTimer>

class RippleButton : public QPushButton {
  Q_OBJECT
  Q_PROPERTY(qreal rippleRadius READ rippleRadius WRITE setRippleRadius)
public:
  explicit RippleButton(QWidget *parent = nullptr);

  qreal rippleRadius() const;
  void setRippleRadius(qreal radius);

protected:
  void paintEvent(QPaintEvent *) override;
  void mousePressEvent(QMouseEvent *e) override;
  void resizeEvent(QResizeEvent *event) override;

private:
  QPointF m_click_position;
  qreal m_ripple_radius;
  QPropertyAnimation *m_animation;

private slots:
  void onRippleFinished();
};

#endif // RIPPLEBUTTON_H
