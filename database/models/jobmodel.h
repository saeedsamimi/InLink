#ifndef JOBMODEL_H
#define JOBMODEL_H
#include <QString>

class JobModel {
public:
  JobModel(unsigned int id, const QString &name, const QString &jobType,
           const QString &location, const QString &jobMode);

  /* Getters */

  QString getName() const;
  QString getJobType() const;
  QString getLocation() const;
  QString getJobMode() const;

private:
  unsigned int id;
  QString name;
  QString jobType;
  QString location;
  QString jobMode;
};

#endif // JOBMODEL_H
