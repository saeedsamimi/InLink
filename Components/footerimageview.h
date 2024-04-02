#ifndef FOOTERIMAGEVIEW_H
#define FOOTERIMAGEVIEW_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QWidget>

class FooterImageView : public QGraphicsView {
 public:
  FooterImageView(QWidget *parent = nullptr);

  QPixmap pixmap() const;

  void setPixmap(const QPixmap &newPixmap);

  void resizeEvent(QResizeEvent *event);

  void resizeImg(const QRectF &target);

  void scrollContentsBy(int, int) override;

 private:
  QGraphicsPixmapItem *m_footerPixmap;
};

#endif  // FOOTERIMAGEVIEW_H
