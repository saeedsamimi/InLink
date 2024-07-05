#ifndef JOBMODEL_H
#define JOBMODEL_H
#include <QString>
class UserModel;

class JobModel {
public:
  enum JobRequestStatus { Pending, NotRequested, Accepted, Rejected };
  JobModel(unsigned int id, const QString &name, const QString &jobType,
           const QString &location, const QString &jobMode);

  /* Getters */

  QString getName() const;
  QString getJobType() const;
  QString getLocation() const;
  QString getJobMode() const;
  unsigned int getId() const;
  JobRequestStatus getStatus() const;
  void loadStatus(UserModel *user);

  static JobRequestStatus statusFromVariant(const QVariant &v);

private:
  unsigned int id;
  QString name;
  QString jobType;
  QString location;
  QString jobMode;
  JobRequestStatus status;
};

#include <database/models/usermodel.h>

#endif // JOBMODEL_H
