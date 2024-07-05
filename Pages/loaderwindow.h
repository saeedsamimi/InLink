#ifndef LOADERWINDOW_H
#define LOADERWINDOW_H

#include <QHBoxLayout>
#include <QLabel>
#include <QMovie>
#include <QPaintEvent>
#include <QParallelAnimationGroup>
#include <QWidget>

class LoaderWindow : public QWidget {
  Q_OBJECT
  Q_PROPERTY(qreal y1 READ getY1 WRITE setY1)
  Q_PROPERTY(qreal index READ getIndex WRITE setIndex)

public:
  LoaderWindow(int id, int activationLevel, QWidget *parent = nullptr);
  ~LoaderWindow();

  qreal getY1() const;
  void setY1(qreal new_v);

  qreal getIndex() const;
  void setIndex(qreal new_v);

signals:
  void onLoadingFinished();

protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

protected slots:
  void handleChangeFrame(int);

private:
  QMovie loaderMovie;
  QPointF prev_mouse_location;
  QParallelAnimationGroup animations;
  qreal y1;
  qreal index;
};

inline qreal LoaderWindow::getY1() const { return this->y1; }

inline qreal LoaderWindow::getIndex() const { return this->index; }

#endif // LOADERWINDOW_H
