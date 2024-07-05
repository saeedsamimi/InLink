#include "jobdelegate.h"
#include "ui_jobdelegate.h"

JobDelegate::JobDelegate(const JobModel &job, QWidget *parent)
    : QWidget(parent), m_job(job), ui(new Ui::JobDelegate) {
  ui->setupUi(this);
  ui->job_title_lbl->setText(m_job.getName());
  ui->job_location_lbl->setText(m_job.getLocation());
  ui->job_type_lb->setText(m_job.getJobMode() + " - " + m_job.getJobType());
  switch (m_job.getStatus()) {
  case JobModel::Accepted:
    ui->apply_btn->setText("Accepted!");
    ui->apply_btn->setEnabled(false);
    break;
  case JobModel::NotRequested:
    ui->apply_btn->setText("Apply");
    break;
  case JobModel::Rejected:
    ui->apply_btn->setText("Rejected");
    ui->apply_btn->setEnabled(false);
    break;
  case JobModel::Pending:
    ui->apply_btn->setText("Pending");
    ui->apply_btn->setEnabled(false);
    break;
  default:
    throw std::exception();
  }
}

JobDelegate::~JobDelegate() { delete ui; }

void JobDelegate::on_apply_btn_clicked() {
  emit onJobRequsted(&m_job);
  ui->apply_btn->setEnabled(false);
}
