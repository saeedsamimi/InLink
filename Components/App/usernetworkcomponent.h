#ifndef USERNETWORKCOMPONENT_H
#define USERNETWORKCOMPONENT_H

#include <QListWidgetItem>
#include <QWidget>
#include <database/models/usermodel.h>

namespace Ui {
class UserNetworkComponent;
}

class UserNetworkComponent : public QWidget {
  Q_OBJECT

public:
  explicit UserNetworkComponent(UserModel *model, QWidget *parent = nullptr);
  ~UserNetworkComponent();

private slots:
  void handleFinishInvitation(UserModel *user, bool state,
                              QListWidgetItem *item);

private:
  Ui::UserNetworkComponent *ui;
  UserModel *model;
};

#endif // USERNETWORKCOMPONENT_H
