#include "companyjobcomponent.h"
#include "ui_companyjobcomponent.h"
#include <Components/Dialogs/createjobdialog.h>

CompanyJobComponent::CompanyJobComponent(const CompanyModel &model,
                                         QWidget *parent)
    : QWidget(parent), ui(new Ui::CompanyJobComponent), model(model) {
  ui->setupUi(this);
}

CompanyJobComponent::~CompanyJobComponent() { delete ui; }

void CompanyJobComponent::on_create_job_btn_clicked() {
  CreateJobDialog create_job_dialog(this);
  create_job_dialog.execute(&model);
}
