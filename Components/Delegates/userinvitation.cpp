#include "userinvitation.h"
#include "ui_userinvitation.h"

UserInvitation::UserInvitation(QListWidgetItem *item, QPair<int, bool> data,
                               QWidget *parent)
    : QWidget(parent), ui(new Ui::UserInvitation), model(data.first),
      item(item) {
  ui->setupUi(this);
  ui->profile_lbl->setPixmap(model.getUserProfile());
  ui->username_lbl->setText(model.getFirstName() + " " + model.getLastName());
  if (!data.second) {
    ui->accept_btn->hide();
    ui->reject_btn->setText("Rejected");
    ui->reject_btn->setEnabled(false);
  }
}

UserInvitation::~UserInvitation() { delete ui; }

void UserInvitation::on_accept_btn_clicked() {
  emit finished(&model, true, item);
}

void UserInvitation::on_reject_btn_clicked() {
  emit finished(&model, false, item);
  ui->accept_btn->hide();
  ui->reject_btn->setText("Rejected");
  ui->reject_btn->setEnabled(false);
}
