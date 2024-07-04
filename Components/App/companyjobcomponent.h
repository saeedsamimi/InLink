#ifndef COMPANYJOBCOMPONENT_H
#define COMPANYJOBCOMPONENT_H

#include <QWidget>
#include <database/models/companymodel.h>

namespace Ui {
class CompanyJobComponent;
}

class CompanyJobComponent : public QWidget {
  Q_OBJECT

public:
  explicit CompanyJobComponent(const CompanyModel &model,
                               QWidget *parent = nullptr);
  ~CompanyJobComponent();

private slots:
  void on_create_job_btn_clicked();

private:
  Ui::CompanyJobComponent *ui;
  CompanyModel model;
};

#endif // COMPANYJOBCOMPONENT_H
