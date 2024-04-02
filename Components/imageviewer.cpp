#include "imageviewer.h"

ImageViewer::ImageViewer(QWidget *parent) : QGraphicsView(parent) {
  setScene(new QGraphicsScene(this));
  setStyleSheet("background: transparent;border: none");
  m_pixmapItem = scene()->addPixmap(QPixmap());
  setAlignment(Qt::AlignCenter);
}

QPixmap ImageViewer::pixmap() const { return m_pixmapItem->pixmap(); }

void ImageViewer::setPixmap(const QPixmap &newPixmap) {
  m_pixmapItem->setPixmap(newPixmap);
  fitInView(m_pixmapItem, Qt::KeepAspectRatio);
}

void ImageViewer::resizeEvent(QResizeEvent *event) {
  QGraphicsView::resizeEvent(event);
  fitInView(m_pixmapItem, Qt::KeepAspectRatio);
}
