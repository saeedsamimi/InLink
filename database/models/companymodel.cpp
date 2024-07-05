#include "companymodel.h"

// clang-format off
const QLatin1String GET_COMPANY_FROM_USER(R"(SELECT name FROM app_companies WHERE owner = ?)");

const QLatin1String SIGNUP_NEW_COMPANY(R"(INSERT INTO app_companies (owner,name) VALUES (?,?))");

const QLatin1String REGISTER_NEW_JOB(R"(INSERT INTO job_positions (owner_id,job_name,job_mode,job_location,job_type) VALUES (?,?,?,?,?))");

const QLatin1String GET_ALL_REQUESTS(
R"(WITH t_companies AS(SELECT c.owner,c.name FROM app_companies c JOIN users u ON u.id = c.owner WHERE u.isCompany = true)
SELECT request_id,user_id, r.job_id, job_name,status
FROM job_requests r JOIN job_positions j ON r.job_id = j.job_id JOIN t_companies t ON t.owner = j.owner_id WHERE j.owner_id = ?)"
);
// clang-format on

CompanyModel::CompanyModel(QObject *parent) : QObject{parent} {}

CompanyModel::CompanyModel(const CompanyModel &other)
    : ownerId(other.ownerId), name(other.name) {}

CompanyModel CompanyModel::FromUser(UserModel *model) {
  int userId = model->getId();
  CREATE_SQL(GET_COMPANY_FROM_USER);
  SQL_BIND(userId);
  if (!query.exec())
    SQL_THROW;
  if (query.next()) {
    CompanyModel company_model;
    company_model.ownerId = userId;
    company_model.name = query.value(0).toString();
    return company_model;
  } else
    throw UserNotFoundException();
}

CompanyModel CompanyModel::SignUpByUser(UserModel *model, QString name) {
  model->signUpAsCompany();
  int userId = model->getId();
  CREATE_SQL(SIGNUP_NEW_COMPANY);
  SQL_BIND(userId);
  SQL_BIND(name);
  if (!query.exec())
    SQL_THROW;
  CompanyModel company_model;
  company_model.ownerId = userId;
  company_model.name = name;
  return company_model;
}

int CompanyModel::getId() const { return ownerId; }

QString CompanyModel::getName() const { return name; }

void CompanyModel::createJob(const QString &name, const QString &jobMode,
                             const QString &location, const QString &jobType) {
  CREATE_SQL(REGISTER_NEW_JOB);
  SQL_BIND(ownerId);
  SQL_BIND(name);
  SQL_BIND(jobMode);
  SQL_BIND(location);
  SQL_BIND(jobType);
  if (!query.exec())
    SQL_THROW;
}

QList<JobRequestModel> CompanyModel::getRequests() const {
  CREATE_SQL(GET_ALL_REQUESTS);
  SQL_BIND(ownerId);
  if (query.exec()) {
    QList<JobRequestModel> requests;
    while (query.next())
      requests.emplace_back(query.value(0).toUInt(), query.value(1).toUInt(),
                            query.value(2).toUInt(), query.value(3).toString(),
                            JobModel::statusFromVariant(query.value(4)));
    return requests;
  } else
    SQL_THROW;
}
