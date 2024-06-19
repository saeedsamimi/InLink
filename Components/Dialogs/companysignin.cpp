#include "companysignin.h"
#include "ui_companysignin.h"

CompanySignIn::CompanySignIn(UserModel *model, QWidget *parent)
    : QDialog(parent), ui(new Ui::CompanySignIn), model(model) {
  ui->setupUi(this);
  ui->firstname_input->setText(model->getFirstName());
  ui->lastname_input->setText(model->getLastName());
}

CompanySignIn::~CompanySignIn() { delete ui; }

void CompanySignIn::on_dialogButtonBox_accepted() {
  QString text = ui->company_name_input->text();
  if (!text.isEmpty()) {
    this->close();
    // enable changes in the database and emit the signal
    emit onSigned(CompanyModel::SignUpByUser(model, text));
  }
}

void CompanySignIn::on_dialogButtonBox_rejected() { this->close(); }
