#ifndef JOBSCOMPONENT_H
#define JOBSCOMPONENT_H

#include <QWidget>
#include <database/models/usermodel.h>

namespace Ui {
class UserJobsComponent;
}

class UserJobsComponent : public QWidget {
  Q_OBJECT

public:
  explicit UserJobsComponent(UserModel *model, QWidget *parent = nullptr);
  ~UserJobsComponent();

private slots:
  void handleJobRequest(JobModel *);

private:
  Ui::UserJobsComponent *ui;
  UserModel *model;
};

#endif // JOBSCOMPONENT_H
