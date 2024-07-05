#ifndef JOBREQUESTDELEGATE_H
#define JOBREQUESTDELEGATE_H

#include <QWidget>
#include <database/models/jobrequestmodel.h>

namespace Ui {
class JobRequestDelegate;
}

class JobRequestDelegate : public QWidget {
  Q_OBJECT

public:
  explicit JobRequestDelegate(const JobRequestModel &model,
                              QWidget *parent = nullptr);
  ~JobRequestDelegate();

private slots:
  void on_accept_btn_clicked();

  void on_reject_btn_clicked();

private:
  Ui::JobRequestDelegate *ui;
  JobRequestModel model;

  void utilUpdateState(JobModel::JobRequestStatus status);
};

#endif // JOBREQUESTDELEGATE_H
