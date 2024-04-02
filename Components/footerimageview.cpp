#include "footerimageview.h"

FooterImageView::FooterImageView(QWidget *parent) : QGraphicsView(parent) {
  setScene(new QGraphicsScene(this));
  setStyleSheet("background-color: transparent;border: none;");
  m_footerPixmap = scene()->addPixmap(QPixmap());
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

QPixmap FooterImageView::pixmap() const { return m_footerPixmap->pixmap(); }

void FooterImageView::setPixmap(const QPixmap &newPixmap) {
  m_footerPixmap->setPixmap(newPixmap);
  resizeImg(rect());
}

void FooterImageView::resizeEvent(QResizeEvent *event) {
  resizeImg(rect());
  QGraphicsView::resizeEvent(event);
}

void FooterImageView::resizeImg(const QRectF &target) {
  QTransform tr;
  QRectF dest = m_footerPixmap->boundingRect();
  double wsx = target.width() / dest.width();
  tr.scale(wsx, wsx);
  tr.translate(0, target.height() - dest.height());
  m_footerPixmap->setTransform(tr);
}

void FooterImageView::scrollContentsBy(int, int) {}
