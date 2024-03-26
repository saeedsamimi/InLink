#ifndef FOOTERIMAGEVIEW_H
#define FOOTERIMAGEVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsItem>

class FooterImageView : public QGraphicsView
{
public:
    FooterImageView(QWidget*parent = nullptr);

    QPixmap pixmap() const;

    void setPixmap(const QPixmap &newPixmap);

    void resizeEvent(QResizeEvent *event);

    void resizeImg(const QRectF &target);

    void scrollContentsBy(int,int) override;
private:
    QGraphicsPixmapItem *m_footerPixmap;
};

#endif // FOOTERIMAGEVIEW_H
