#include "usernetworkcomponent.h"
#include "ui_usernetworkcomponent.h"
#include <Components/Delegates/userinvitation.h>

UserNetworkComponent::UserNetworkComponent(UserModel *model, QWidget *parent)
    : QWidget(parent), ui(new Ui::UserNetworkComponent), model(model) {
  ui->setupUi(this);
  for (auto item : model->getAllPendingInvitations()) {
    auto widget_item = new QListWidgetItem();
    auto custom_widget = new UserInvitation(widget_item, item);
    widget_item->setSizeHint(custom_widget->sizeHint());
    ui->invitations_list->addItem(widget_item);
    ui->invitations_list->setItemWidget(widget_item, custom_widget);
    connect(custom_widget, &UserInvitation::finished, this,
            &UserNetworkComponent::handleFinishInvitation);
  }
}

UserNetworkComponent::~UserNetworkComponent() { delete ui; }

void UserNetworkComponent::handleFinishInvitation(UserModel *user, bool state,
                                                  QListWidgetItem *item) {
  if (state) {
    model->acceptFollow(user->getId());
    ui->invitations_list->removeItemWidget(item);
    delete item;
  } else
    model->rejectFollow(user->getId());
}
