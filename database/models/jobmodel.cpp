#include "jobmodel.h"

JobModel::JobModel(unsigned int id, const QString &name, const QString &jobType,
                   const QString &location, const QString &jobMode)
    : id(id), name(name), jobType(jobType), location(location),
      jobMode(jobMode) {}

QString JobModel::getName() const { return name; }

QString JobModel::getJobType() const { return jobType; }

QString JobModel::getLocation() const { return location; }

QString JobModel::getJobMode() const { return jobMode; }
