#include "companysignin.h"
#include "ui_companysignin.h"

CompanySignIn::CompanySignIn(QWidget *parent)
    : QDialog(parent), ui(new Ui::CompanySignIn) {
  ui->setupUi(this);
}

CompanySignIn::~CompanySignIn() { delete ui; }

void CompanySignIn::on_dialogButtonBox_accepted() {
  this->close();
  emit onSigned();
}

void CompanySignIn::on_dialogButtonBox_rejected() {
  this->close();
  emit onCanceled();
}
