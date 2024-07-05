#include "loaderwindow.h"
#include <Pages/codeverifier.h>
#include <Pages/completeprofile.h>
#include <Pages/mainwindow.h>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimer>
#include <database/user.h>

LoaderWindow::LoaderWindow(int id, int activationLevel, QWidget *parent)
    : QWidget(parent), loaderMovie(":/ico-anim-light.gif"), animations(this) {
  setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
  setMouseTracking(true);
  loaderMovie.start();
  connect(&loaderMovie, &QMovie::frameChanged, this,
          &LoaderWindow::handleChangeFrame);
  setFixedSize(500, 600);
  QPropertyAnimation *animation = new QPropertyAnimation(this, "y1", this);
  animation->setKeyValues(
      {{0.0, 0}, {0.25, 20}, {0.5, 0}, {0.75, -20}, {1.0, 0}});
  animation->setDuration(1500);
  animation->setLoopCount(-1);
  animation->setEasingCurve(QEasingCurve::InOutQuad);
  animations.addAnimation(animation);
  QPropertyAnimation *indexAnimation =
      new QPropertyAnimation(this, "index", this);
  indexAnimation->setKeyValues({{0.0, 0}, {0.5, 5}, {1.0, 0}});
  indexAnimation->setDuration(1500);
  indexAnimation->setLoopCount(-1);
  animations.addAnimation(animation);
  animations.addAnimation(indexAnimation);
  animations.start();
  QFont m_font = font();
  m_font.setBold(true);
  setFont(m_font);
  QTimer::singleShot(1000, this, [this, id, activationLevel]() {
    QWidget *win;
    // make decision
    if (activationLevel == Added)
      win = new CodeVerifier(id);
    else if (activationLevel == Activated)
      win = new CompleteProfile(id);
    else
      win = new MainWindow(id);
    win->connect(win, &QWidget::destroyed, &QWidget::deleteLater);
    win->show();
    this->close();
  });
}

LoaderWindow::~LoaderWindow() {}

void LoaderWindow::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  QImage currentImage(loaderMovie.currentImage());
  painter.drawImage(0, 0, currentImage.scaled(500, 500, Qt::KeepAspectRatio), 0,
                    0, 500, 500);
  painter.translate(70, 530);
  painter.setBrush(palette().accent().color());
  painter.setPen(Qt::NoPen);
  for (int i = 0; i < 5; i++) {
    painter.translate(60, 0);
    painter.setOpacity(1.0 - std::abs(i - index) * 0.2);
    painter.drawEllipse(
        QPointF(0.0, std::cos(M_PI / 2 * std::abs(i - index)) * y1), 10, 10);
  }
  painter.setOpacity(1.0);
  painter.setPen(palette().text().color());
  painter.translate(-145, 50);
  painter.drawText(0, 0, "Loading");
}

void LoaderWindow::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton)
    prev_mouse_location = event->globalPosition();
}

void LoaderWindow::mouseMoveEvent(QMouseEvent *event) {
  if (!prev_mouse_location.isNull()) {
    QPointF delta = event->globalPosition() - prev_mouse_location;
    move(x() + delta.x(), y() + delta.y());
    prev_mouse_location = event->globalPosition();
  }
}

void LoaderWindow::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton)
    prev_mouse_location = QPointF();
}

void LoaderWindow::handleChangeFrame(int) { update(); }

void LoaderWindow::setY1(qreal _v) {
  y1 = _v;
  update();
}

void LoaderWindow::setIndex(qreal new_v) {
  index = new_v;
  update();
}
