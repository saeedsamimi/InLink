#include "jobmodel.h"
#include <utils/Util.h>

// clang-format off
const QLatin1String GET_JOB_REQUEST_STATUS(R"(SELECT status FROM job_requests WHERE job_id = ? AND user_id = ?)");
// clang-format on

JobModel::JobModel(unsigned int id, const QString &name, const QString &jobType,
                   const QString &location, const QString &jobMode)
    : id(id), name(name), jobType(jobType), location(location),
      jobMode(jobMode) {}

QString JobModel::getName() const { return name; }

QString JobModel::getJobType() const { return jobType; }

QString JobModel::getLocation() const { return location; }

QString JobModel::getJobMode() const { return jobMode; }

unsigned int JobModel::getId() const { return id; }

JobModel::JobRequestStatus JobModel::getStatus() const { return status; }

void JobModel::loadStatus(UserModel *user) {
  CREATE_SQL(GET_JOB_REQUEST_STATUS);
  SQL_BIND(id);
  SQL_BIND(user->getId());
  if (query.exec())
    status = query.next() ? statusFromVariant(query.value(0)) : NotRequested;
  else
    SQL_THROW;
}

JobModel::JobRequestStatus JobModel::statusFromVariant(const QVariant &v) {
  if (v.isNull())
    return Pending;
  return v.toBool() ? Accepted : Rejected;
}
