#include "user.h"

#include "dbinit.h"
#include "encryption.hpp"
#include <utils/Util.h>

const char *identity_list[12] = {"first_name", "last_name", "birth_date",
                                 "country",    "city",      "school",
                                 "start_year", "end_year",  "is_student",
                                 "recent_job", "emp_type",  "recent_company"};

void insertUser(const QString &username, const QString &password) {
  CREATE_SQL(INSERT_USER_SQL);
  // handle in-insert errors
  SQL_BIND(username);
  SQL_BIND(hashUsingSHA256(password));
  // error codes:
  //        23505:
  //            the user is already exists!
  if (!query.exec())
    if (query.lastError().nativeErrorCode().toInt() == 23505)
      throw QObject::tr("This username already exists!");
    else
      SQL_THROW;
}

int validateUser(const QString &username, const QString &password) {
  CREATE_SQL(FIND_USER_SQL);
  // handle in-find errors
  SQL_BIND(username);
  // no error code is provided
  if (!query.exec())
    SQL_THROW;
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
  CREATE_SQL(GET_USERS_ID_SQL);
  // find the user's ID in db
  SQL_BIND(username);
  // the returns always win if the argument username is true!
  if (!query.exec())
    SQL_THROW;
  query.next();
  return query.value(query.record().indexOf("ID")).toInt();
}

int addAccount(const QString &username, const QString &password) {
  saveLoginInfo(username, password, "login.dat", generateKey());
  return getUserID(username);
}

void changeAccountLevel(int ID, UserLevel level) {
  CREATE_SQL(UPDATE_ACCOUNT_LEVEL_SQL);
  // handle in-find errors
  SQL_BIND(level);
  SQL_BIND(ID);
  if (!query.exec())
    SQL_THROW;
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
  CREATE_SQL(UPDATE_USER_IDENTITIES_SQL.arg(identity));
  // this function is capable to have errors so the error handling have to
  // enabled for that
  SQL_BIND(value);
  SQL_BIND(ID);
  // execute the query
  if (!query.exec())
    SQL_THROW;
}

void updateUserIdentity(int ID, UserIdentity identity, const QVariant &value) {
  updateUserIdentity(ID, identity_list[identity], value);
}

QString getUsername(int ID) {
  CREATE_SQL(GET_USERNAME_SQL);
  query.addBindValue(ID);
  if (!query.exec())
    SQL_THROW;
  query.next();
  return query.value(0).toString();
}

int getUserActivationLevel(const QString &username) {
  CREATE_SQL(GET_USER_ACTIVATION_LEVEL);
  SQL_BIND(username);
  if (query.exec()) {
    query.next();
    return (UserLevel)query.value(0).toInt();
  } else
    SQL_THROW;
  return -1;
}
