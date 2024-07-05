#include "companyjobcomponent.h"
#include "ui_companyjobcomponent.h"
#include <Components/Delegates/jobrequestdelegate.h>
#include <Components/Dialogs/createjobdialog.h>

CompanyJobComponent::CompanyJobComponent(const CompanyModel &model,
                                         QWidget *parent)
    : QWidget(parent), ui(new Ui::CompanyJobComponent), model(model) {
  ui->setupUi(this);
  QList<JobRequestModel> requests = model.getRequests();
  for (JobRequestModel &request : requests) {
    QListWidgetItem *item = new QListWidgetItem(ui->requests_list);
    JobRequestDelegate *delegate = new JobRequestDelegate(request);
    item->setSizeHint(delegate->sizeHint());
    ui->requests_list->addItem(item);
    ui->requests_list->setItemWidget(item, delegate);
  }
}

CompanyJobComponent::~CompanyJobComponent() { delete ui; }

void CompanyJobComponent::on_create_job_btn_clicked() {
  CreateJobDialog create_job_dialog(this);
  create_job_dialog.execute(&model);
}
