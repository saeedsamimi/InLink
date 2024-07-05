#ifndef JOBREQUESTMODEL_H
#define JOBREQUESTMODEL_H
#include <database/models/jobmodel.h>

struct JobRequestModel {
public:
  unsigned int request_id;
  unsigned int user_id;
  unsigned int job_id;
  QString job_name;
  JobModel::JobRequestStatus status;

  void accept();
  void reject();

private:
  void util(bool v);
};

#endif // JOBREQUESTMODEL_H
