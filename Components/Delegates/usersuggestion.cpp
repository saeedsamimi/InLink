#include "usersuggestion.h"
#include "ui_usersuggestion.h"
#include <Components/Dialogs/showprofiledialog.h>
#include <utils/Util.h>

UserSuggestion::UserSuggestion(bool isCompany, const UserModel &model,
                               QWidget *parent)
    : QWidget(parent), ui(new Ui::UserSuggestion), model(model) {
  ui->setupUi(this);
  auto prof = model.getUserProfile();
  if (!prof.isNull())
    ui->profile_lbl->setPixmap(prof);
  ui->usernamelbl->setText(model.getUsername());
  ui->job_lbl->setText(model.getJob());
  ui->follow_btn->setText(util::labels[isCompany][0]);
}

UserSuggestion::~UserSuggestion() { delete ui; }

void UserSuggestion::on_close_btn_clicked() { emit onClosed(); }

void UserSuggestion::on_follow_btn_clicked() {
  emit onFollow();
  emit onClosed();
}

void UserSuggestion::on_view_profile_btn_clicked() {
  ShowProfileDialog dialog(&model, this);
  dialog.exec();
}
