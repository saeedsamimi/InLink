#include "usermodel.h"

#include <QSqlQuery>

const QLatin1String LOAD_USER_SQL(
    R"(SELECT username,first_name,last_name,emp_type FROM users WHERE ID = ?;)");

UserModel::UserModel(int id) : id(id) {
  QSqlQuery query;
  // handle client errors
  if (!query.prepare(LOAD_USER_SQL)) throw query.lastError();
  query.addBindValue(id);
  if (query.exec()) {
    if (query.next()) {
      m_username = query.value(0).toString();
      m_firstname = query.value(1).toString();
      m_lastname = query.value(2).toString();
      m_employment_type = query.value(3).toString();
    } else
      throw UserNotFoundException();
  } else
    throw query.lastError();
}

int UserModel::getId() const { return id; }

const QString &UserModel::getUsername() const { return m_username; }

const QString &UserModel::getFirstName() const { return m_firstname; }

const QString &UserModel::getLastName() const { return m_lastname; }

const QString &UserModel::getEmploymentType() const {
  return m_employment_type;
}

UserNotFoundException::~UserNotFoundException() noexcept {}

const char *UserNotFoundException::what() const noexcept {
  return "The User not found";
}
