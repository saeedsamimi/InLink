#ifndef USERCARD_H
#define USERCARD_H

#include <QListWidgetItem>
#include <QWidget>
#include <database/models/usermodel.h>

namespace Ui {
class UserInvitation;
}

class UserInvitation : public QWidget {
  Q_OBJECT

public:
  explicit UserInvitation(QListWidgetItem *item, QPair<int, bool> follow,
                          QWidget *parent = nullptr);
  ~UserInvitation();

signals:
  void finished(UserModel *model, bool, QListWidgetItem *item);

private slots:
  void on_accept_btn_clicked();

  void on_reject_btn_clicked();

private:
  Ui::UserInvitation *ui;
  UserModel model;
  QListWidgetItem *item;
};

#endif // USERCARD_H
