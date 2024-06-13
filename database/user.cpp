#include "user.h"

#include "dbinit.h"
#include "encryption.hpp"

const char *identity_list[12] = {"first_name", "last_name", "birth_date",
                                 "country",    "city",      "school",
                                 "start_year", "end_year",  "is_student",
                                 "recent_job", "emp_type",  "recent_company"};

void insertUser(const QString &username, const QString &password) {
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(INSERT_USER_SQL))
    throw query.lastError();
  // handle in-insert errors
  query.addBindValue(username);
  query.addBindValue(hashUsingSHA256(password));
  // error codes:
  //        23505:
  //            the user is already exists!
  if (!query.exec())
    if (query.lastError().nativeErrorCode().toInt() == 23505)
      throw QObject::tr("This username already exists!");
    else
      throw query.lastError();
}

int validateUser(const QString &username, const QString &password) {
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(FIND_USER_SQL))
    throw query.lastError();
  // handle in-find errors
  query.addBindValue(username);
  // no error code is provided
  if (!query.exec())
    throw query.lastError();
  if (query.next()) {
    // returns if the user password correct otherwise gives an exception
    if (query.value(1).toString() != hashUsingSHA256(password))
      throw QPair<QString, bool>(QObject::tr("This password is incorrect!"),
                                 false);
    return query.value(0).toInt();
  } else { // throw error if the user is not exists
    throw QPair<QString, bool>(
        QObject::tr("This user is not exist, do you want to sign in?"), true);
  }
  return -1;
}

int getUserID(const QString &username) {
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(GET_USERS_ID_SQL))
    throw query.lastError();
  // find the user's ID in db
  query.addBindValue(username);
  // the returns always win if the argument username is true!
  if (!query.exec())
    qDebug() << query.lastError();
  query.next();
  return query.value(query.record().indexOf("ID")).toInt();
}

int addAccount(const QString &username, const QString &password) {
  saveLoginInfo(username, password, "login.dat", generateKey());
  return getUserID(username);
}

void changeAccountLevel(int ID, UserLevel level) {
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(UPDATE_ACCOUNT_LEVEL_SQL))
    throw query.lastError();
  // handle in-find errors
  query.addBindValue(level);
  query.addBindValue(ID);
  if (!query.exec())
    throw query.lastError();
}

bool getActiveAccountUser(int &user_id, int &active_level) {
  QStringList data = readLoginInfo("login.dat", generateKey());
  if (data.length() != 2)
    return false; // the data is incorrect

  QString username = data[0];
  QString password(data[1]);

  user_id = active_level = -1;

  try {
    user_id = validateUser(username, password);
    active_level = getUserActivationLevel(username);
  } catch (QPair<QString, bool> &err) {
    return false;
  } catch (QSqlError &err) {
    throw;
  }

  return true;
}

void updateUserIdentity(int ID, const char *identity, const QVariant &value) {
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(UPDATE_USER_IDENTITIES_SQL.arg(identity)))
    throw query.lastError();
  // this function is capable to have errors so the error handling have to
  // enabled for that
  query.addBindValue(value);
  query.addBindValue(ID);
  // execute the query
  if (!query.exec()) {
    QSqlError lasterr = query.lastError();
    qDebug() << "Line 114 of user.cpp throws an error : " << lasterr;
    throw lasterr;
  }
}

void updateUserIdentity(int ID, UserIdentity identity, const QVariant &value) {
  updateUserIdentity(ID, identity_list[identity], value);
}

QString getUsername(int ID) {
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(GET_USERNAME_SQL))
    throw query.lastError();
  query.addBindValue(ID);
  if (!query.exec())
    qDebug() << query.lastError();
  query.next();
  return query.value(0).toString();
}

int getUserActivationLevel(const QString &username) {
  QSqlQuery query;
  if (!query.prepare(GET_USER_ACTIVATION_LEVEL))
    throw query.lastError();
  query.addBindValue(username);
  if (query.exec()) {
    query.next();
    return (UserLevel)query.value(0).toInt();
  } else
    return -1;
}
