#include "waitformorefeature.h"

#include "ui_waitformorefeature.h"

WaitForMoreFeature::WaitForMoreFeature(int ID, QWidget *parent)
    : QDialog(parent), query{}, ui(new Ui::WaitForMoreFeature), ID(ID) {
  ui->setupUi(this);
  query.prepare(
      "SELECT username, last_view FROM accounts INNER JOIN users ON users.ID = "
      "accounts.user_ID WHERE ID = ?");
  query.addBindValue(ID);
  if (!query.exec()) qDebug() << "Error occurred!";
  query.next();
  ui->usernameLbl->setText(
      QString("Username: %1").arg(query.value(0).toString()));
  ui->lastviewLbl->setText(
      QString("Last View: %1").arg(query.value(1).toString()));
}

WaitForMoreFeature::~WaitForMoreFeature() { delete ui; }

void WaitForMoreFeature::on_buttonBox_rejected() {
  query.prepare("DELETE FROM accounts WHERE user_ID = ?;");
  query.addBindValue(ID);
  query.exec();
}
