#include "showfollowings.h"
#include "ui_showfollowings.h"
#include <Components/Delegates/chatdelegate.h>

ShowFollowings::ShowFollowings(UserModel *model, QWidget *parent)
    : QDialog(parent), ui(new Ui::ShowFollowings), model(model),
      users(model->getFollowedUsers()) {
  ui->setupUi(this);
  for (auto &user : users) {
    QListWidgetItem *item = new QListWidgetItem();
    ChatDelegate *chat_delegate = new ChatDelegate(user);
    item->setSizeHint(chat_delegate->sizeHint());
    ui->users_list->addItem(item);
    ui->users_list->setItemWidget(item, chat_delegate);
  }
}

ShowFollowings::~ShowFollowings() { delete ui; }
