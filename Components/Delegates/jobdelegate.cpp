#include "jobdelegate.h"
#include "ui_jobdelegate.h"

JobDelegate::JobDelegate(const JobModel &job, QWidget *parent)
    : QWidget(parent), m_job(job), ui(new Ui::JobDelegate) {
  ui->setupUi(this);
  ui->job_title_lbl->setText(m_job.getName());
  ui->job_location_lbl->setText(m_job.getLocation());
  ui->job_type_lb->setText(m_job.getJobMode() + " - " + m_job.getJobType());
}

JobDelegate::~JobDelegate() { delete ui; }
