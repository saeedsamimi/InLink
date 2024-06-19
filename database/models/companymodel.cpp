#include "companymodel.h"

// clang-format off
const QLatin1String GET_COMPANY_FROM_USER(R"(SELECT name FROM app_companies WHERE owner = ?)");

const QLatin1String SIGNUP_NEW_COMPANY(R"(INSERT INTO app_companies (owner,name) VALUES (?,?))");
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
