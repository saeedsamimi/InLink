#ifndef MESSAGEDELEGATE_H
#define MESSAGEDELEGATE_H

#include <QDateTime>
#include <QFrame>
#include <QLabel>

namespace Ui {
class MessageDelegate;
}

class MessageDelegate : public QFrame {
  Q_OBJECT

public:
  explicit MessageDelegate(int sender_id, QString contenet,
                           const QString &pixmap_path, QDateTime time,
                           QWidget *parent = nullptr);
  ~MessageDelegate();

private:
  Ui::MessageDelegate *ui;
  QLabel *pic_lbl;
};

#endif // MESSAGEDELEGATE_H
