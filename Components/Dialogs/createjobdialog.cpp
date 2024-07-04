#include "createjobdialog.h"
#include "ui_createjobdialog.h"

CreateJobDialog::CreateJobDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreateJobDialog), queryModel(this) {
  queryModel.setQuery("SELECT job_name FROM jobs");
  ui->setupUi(this);
  ui->job_title_input->setModel(&queryModel);
}

int CreateJobDialog::execute(CompanyModel *model) {
  int result = QDialog::exec();
  if (result == QDialog::Accepted)
    model->createJob(
        ui->job_title_input->currentText(), ui->job_mode_input->currentText(),
        ui->job_location_input->text(), ui->job_type_input->currentText());
  return result;
}

CreateJobDialog::~CreateJobDialog() { delete ui; }
