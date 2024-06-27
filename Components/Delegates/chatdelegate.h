#ifndef CHATDELEGATE_H
#define CHATDELEGATE_H

#include <Components/Dialogs/chatdialog.h>
#include <QMouseEvent>
#include <QWidget>
#include <database/models/usermodel.h>

namespace Ui {
class ChatDelegate;
}

class ChatDelegate : public QWidget {
  Q_OBJECT

public:
  explicit ChatDelegate(int id, QWidget *parent = nullptr);
  ~ChatDelegate();

protected:
  void mousePressEvent(QMouseEvent *event) override;

private:
  Ui::ChatDelegate *ui;
  UserModel *model;
  ChatDialog *dialog;
};

#endif // CHATDELEGATE_H
