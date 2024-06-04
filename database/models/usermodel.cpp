#include "usermodel.h"

#include <QSqlQuery>

// clang-format off
const QLatin1String LOAD_USER_SQL(R"(SELECT username,first_name,last_name,emp_type FROM users WHERE ID = ?;)");

const QLatin1String GET_USER_PROFILE_PICTURE_EXISTENCE(R"(SELECT profile IS NOT NULL FROM accounts WHERE user_ID = ?;)");

const QLatin1String GET_USER_PROFILE_PICTURE(R"(SELECT profile FROM accounts WHERE user_ID = ?;)");

const QLatin1String UPDATE_USER_PROFILE_PICTURE(R"(UPDATE accounts SET profile = ? WHERE user_ID = ?;)");

const QLatin1String DELETE_USER_PROFILE_PICTURE(R"(UPDATE accounts SET profile = null WHERE user_ID = ?;)");

const QLatin1String GET_USER_BIOGRAPHY(R"(SELECT bio FROM accounts WHERE user_ID = ?;)");

const QLatin1String UPDATE_USER_BIOGRAPHY(R"(UPDATE accounts SET bio = ? WHERE user_ID = ?;)");

const QLatin1String GET_USER_ABILITIES(R"(SELECT abilities FROM accounts WHERE user_ID = ?;)");

const QLatin1String UPDATE_USER_ABILITIES(R"(UPDATE accounts SET abilities = ? WHERE user_ID = ?;)");

const QLatin1String GET_USER_JOB(R"(SELECT recent_job FROM users WHERE id = ?;)");
// clang-format on

UserModel::UserModel(int id) : id(id) {
  QSqlQuery query;
  // handle client errors
  if (!query.prepare(LOAD_USER_SQL))
    throw query.lastError();
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

QString UserModel::getJob() const {
  QSqlQuery query;
  if (!query.prepare(GET_USER_JOB))
    throw query.lastError();
  query.addBindValue(id);
  if (query.exec()) {
    query.next();
    return query.value(0).toString();
  }
  throw query.lastError();
}

QPixmap UserModel::getUserProfile() const {
  QSqlQuery query;
  if (!query.prepare(GET_USER_PROFILE_PICTURE))
    throw query.lastError();
  query.addBindValue(id);
  if (query.exec()) {
    query.next();
    QByteArray array = query.value(0).toByteArray();
    QDataStream imageStream(&array, QIODevice::ReadOnly);
    QImage img;
    imageStream >> img;
    return QPixmap::fromImage(img);
  } else
    throw query.lastError();
}

QString UserModel::getBioGraphy() const {
  QSqlQuery query;
  if (!query.prepare(GET_USER_BIOGRAPHY))
    throw query.lastError();
  query.addBindValue(id);
  if (!query.exec())
    throw query.lastError();
  query.next();
  return query.value(0).toString();
}

void UserModel::setBiography(const QString &bio) {
  QSqlQuery query;
  if (!query.prepare(UPDATE_USER_BIOGRAPHY))
    throw query.lastError();
  query.addBindValue(bio);
  query.addBindValue(id);
  if (!query.exec())
    throw query.lastError();
}

void UserModel::setUserProfile(const QImage &data) {
  QSqlQuery query;
  if (!query.prepare(UPDATE_USER_PROFILE_PICTURE))
    throw query.lastError();
  QByteArray imageData;
  QDataStream imageStream(&imageData, QIODevice::WriteOnly);
  imageStream << data;
  query.addBindValue(imageData);
  query.addBindValue(id);
  if (!query.exec())
    throw query.lastError();
}

QList<QString> UserModel::getAbilities() const {
  QSqlQuery query;
  if (!query.prepare(GET_USER_ABILITIES))
    throw query.lastError();
  query.addBindValue(id);
  if (query.exec()) {
    query.next();
    QStringList items = query.value(0).toStringList();
    if (items.begin()->isEmpty())
      items.erase(items.begin());
    return items;
  }
  throw query.lastError();
}

void UserModel::setAbilities(const QList<QString> &newAbilities) {
  QSqlQuery query;
  if (!query.prepare(UPDATE_USER_ABILITIES))
    throw query.lastError();
  query.addBindValue(newAbilities);
  query.addBindValue(id);
  if (!query.exec())
    throw query.lastError();
}

bool UserModel::isHaveProfile() const {
  QSqlQuery query;
  if (!query.prepare(GET_USER_PROFILE_PICTURE_EXISTENCE))
    throw query.lastError();
  query.addBindValue(id);
  if (query.exec()) {
    query.next();
    return query.value(0).toBool();
  } else
    throw query.lastError();
}

void UserModel::deleteProfile() {
  QSqlQuery query;
  if (!query.prepare(DELETE_USER_PROFILE_PICTURE))
    throw query.lastError();
  query.addBindValue(id);
  if (!query.exec())
    throw query.lastError();
}

UserNotFoundException::~UserNotFoundException() noexcept {}

const char *UserNotFoundException::what() const noexcept {
  return "The User not found";
}
