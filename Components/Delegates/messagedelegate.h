#ifndef MESSAGEDELEGATE_H
#define MESSAGEDELEGATE_H

#include <QDateTime>
#include <QFrame>

namespace Ui {
class MessageDelegate;
}

class MessageDelegate : public QFrame {
  Q_OBJECT

public:
  explicit MessageDelegate(int sender_id, QString contenet, QDateTime time,
                           QWidget *parent = nullptr);
  ~MessageDelegate();

private:
  Ui::MessageDelegate *ui;
};

#endif // MESSAGEDELEGATE_H
