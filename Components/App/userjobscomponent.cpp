#include "userjobscomponent.h"
#include "ui_userjobscomponent.h"
#include <Components/Delegates/jobdelegate.h>
#include <QListWidgetItem>

UserJobsComponent::UserJobsComponent(UserModel *model, QWidget *parent)
    : QWidget(parent), model(model), ui(new Ui::UserJobsComponent) {
  ui->setupUi(this);
  auto jobs = model->getAllRelatedJobs();
  for (const auto &job : jobs) {
    QListWidgetItem *item = new QListWidgetItem(ui->jobs_list);
    JobDelegate *delegate = new JobDelegate(job);
    item->setSizeHint(delegate->sizeHint());
    ui->jobs_list->addItem(item);
    ui->jobs_list->setItemWidget(item, delegate);
    connect(delegate, &JobDelegate::onJobRequsted, this,
            &UserJobsComponent::handleJobRequest);
  }
}

UserJobsComponent::~UserJobsComponent() { delete ui; }

void UserJobsComponent::handleJobRequest(JobModel *job_model) {
  model->requestJob(job_model->getId());
}
