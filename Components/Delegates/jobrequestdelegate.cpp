#include "jobrequestdelegate.h"
#include "ui_jobrequestdelegate.h"
#include <utils/Util.h>

JobRequestDelegate::JobRequestDelegate(const JobRequestModel &request,
                                       QWidget *parent)
    : QWidget(parent), model(request), ui(new Ui::JobRequestDelegate) {
  ui->setupUi(this);
  ui->job_name_lbl->setText(
      util::buildColoredLabeled("For Job", "3434FF", request.job_name));
  UserModel model(request.user_id);
  ui->pic_lbl->setScaledContents(true);
  ui->pic_lbl->setPixmap(model.getUserProfile());
  ui->username_lbl->setText(util::buildColoredLabeled(
      "Requested From", "3434FF", model.getUsername()));
  utilUpdateState(request.status);
}

JobRequestDelegate::~JobRequestDelegate() { delete ui; }

void JobRequestDelegate::on_accept_btn_clicked() {
  model.accept();
  utilUpdateState(JobModel::Accepted);
}

void JobRequestDelegate::on_reject_btn_clicked() {
  model.reject();
  utilUpdateState(JobModel::Rejected);
}

void JobRequestDelegate::utilUpdateState(JobModel::JobRequestStatus status) {
  if (status != JobModel::Pending) {
    delete ui->accept_btn;
    delete ui->reject_btn;
    QLabel *state_lbl = new QLabel(
        status == JobModel::Accepted ? "Accepted!" : "Rejected!", this);
    state_lbl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    state_lbl->setMaximumSize(100, 40);
    ui->gridLayout->addWidget(state_lbl, 0, 2, 2, 1);
  }
}
