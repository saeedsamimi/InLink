#ifndef ICONBADGES_H
#define ICONBADGES_H
#include <QWidget>

class IconBadges : public QWidget {
  Q_OBJECT
  Q_PROPERTY(unsigned int counter READ counterValue WRITE setCounterValue NOTIFY
                 counterValueChanged FINAL)
public:
  explicit IconBadges(QWidget *parent = nullptr);

  void setIcon(int, const QPixmap & = QPixmap());
  unsigned int counterValue() const;
  void setCounterValue(unsigned int);
  void increaseValue(unsigned int = 1);
  void decreaseValue(unsigned int = 1);

signals:
  void counterValueChanged(unsigned int);
  void clicked();

protected:
  void paintEvent(QPaintEvent *event) override;
  void enterEvent(QEnterEvent *event) override;
  void leaveEvent(QEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
  QPixmap icons[3];
  QPixmap utilTransform(const QPixmap &);
  unsigned int counter;
};

#endif // ICONBADGES_H
