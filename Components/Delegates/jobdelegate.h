#ifndef JOBDELEGATE_H
#define JOBDELEGATE_H

#include <QWidget>
#include <database/models/companymodel.h>

namespace Ui {
class JobDelegate;
}

class JobDelegate : public QWidget {
  Q_OBJECT

public:
  explicit JobDelegate(const JobModel &job, QWidget *parent = nullptr);
  ~JobDelegate();

private:
  Ui::JobDelegate *ui;
  JobModel m_job;
};

#endif // JOBDELEGATE_H
