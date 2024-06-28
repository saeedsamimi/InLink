#include "usernetworkcomponent.h"
#include "ui_usernetworkcomponent.h"
#include <Components/Delegates/userinvitation.h>
#include <Components/Delegates/usersuggestion.h>

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
  if (model->isCompany()) {
    ui->suggest_list->hide();
    ui->suggest_lbl->hide();
  } else {
    for (auto &user : model->getRelatedUsers()) {
      auto widget_item = new QListWidgetItem();
      auto custom_widget = new UserSuggestion(model->isCompany(), user);
      widget_item->setSizeHint(custom_widget->sizeHint());
      ui->suggest_list->addItem(widget_item);
      ui->suggest_list->setItemWidget(widget_item, custom_widget);
      connect(custom_widget, &UserSuggestion::onClosed, this,
              [this, widget_item]() {
                ui->suggest_list->removeItemWidget(widget_item);
                delete widget_item;
              });
      connect(custom_widget, &UserSuggestion::onFollow, this,
              [this, user]() { this->model->follow(user); });
    }
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
