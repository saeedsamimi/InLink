#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>

class ImageViewer : public QGraphicsView {
 public:
  ImageViewer(QWidget *parent = nullptr);
  QPixmap pixmap() const;
  void setPixmap(const QPixmap &newPixmap);

 protected:
  void resizeEvent(QResizeEvent *event);

 private:
  QGraphicsPixmapItem *m_pixmapItem;
};

#endif  // IMAGEVIEWER_H
