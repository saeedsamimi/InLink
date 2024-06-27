#ifndef SHOWFOLLOWINGS_H
#define SHOWFOLLOWINGS_H

#include <QDialog>
#include <QWebSocket>
#include <database/models/usermodel.h>

namespace Ui {
class ShowFollowings;
}

class ShowFollowings : public QDialog {
  Q_OBJECT

public:
  explicit ShowFollowings(UserModel *model, QWidget *parent = nullptr);
  ~ShowFollowings();

private:
  Ui::ShowFollowings *ui;
  UserModel *model;
  QList<int> users;
};

#endif // SHOWFOLLOWINGS_H
