#include "user.h"

#include "dbinit.h"
#include "encryption.h"

const char *identity_list[12] = {"first_name", "last_name", "birth_date",
                                 "country",    "city",      "school",
                                 "start_year", "end_year",  "is_student",
                                 "recent_job", "emp_type",  "recent_company"};

void insertUser(const QString &username, const QString &password) {
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(INSERT_USER_SQL)) throw query.lastError();
  // handle in-insert errors
  query.addBindValue(username);
  query.addBindValue(hashUsingSHA256(password));
  // error codes:
  //        2067:
  //            the user is already exists!
  if (!query.exec())
    if (query.lastError().nativeErrorCode().toInt() == 2067)
      throw QObject::tr("This username already exists!");
    else
      throw query.lastError();
}

void validateUser(const QString &username, const QString &password) {
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(FIND_USER_SQL)) throw query.lastError();
  // handle in-find errors
  query.addBindValue(username);
  // no error code is provided
  if (!query.exec()) throw query.lastError();
  if (query.next()) {
    // returns if the user password correct otherwise gives an exception
    if (query.value(0).toString() != hashUsingSHA256(password))
      throw QPair<QString, bool>(QObject::tr("This password is incorrect!"),
                                 false);
  } else {  // throw error if the user is not exists
    throw QPair<QString, bool>(
        QObject::tr("This user is not exist, do you want to sign in?"), true);
  }
}

bool isUserActivated(const QString &username) {
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(FIND_USER_ACTIVATION_SQL)) throw query.lastError();
  // handle in-find errors
  query.addBindValue(username);
  // no error code is provided
  if (!query.exec()) throw query.lastError();
  if (query.next()) return query.value(0).toBool();
  // we consider  that the user is exists and the query is called correctly
  // so we'll throw an exeption
  throw QSqlError("", "the selected user not exists");
}

void setUserActive(int ID, bool active) {
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(UPDATE_USER_ACTIVATION_SQL)) throw query.lastError();
  // handle in-find errors
  query.addBindValue(active);
  query.addBindValue(ID);
  // no error code is provided
  if (!query.exec()) throw query.lastError();
}

int getUserID(const QString &username) {
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(FIND_USER_SQL)) throw query.lastError();
  // find the user's ID in db
  query.addBindValue(username);
  // the returns always win if the argument username is true!
  if (!query.exec()) qDebug() << query.lastError();
  query.next();
  return query.value(0).toInt();
}

int addAccount(const QString &username) {
  int ID = getUserID(username);
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(ADD_ACCOUNT_SQL)) throw query.lastError();
  query.addBindValue(ID);
  // the return's always win!!!
  if (!query.exec()) qDebug() << query.lastError();
  return ID;
}

void changeAccountLevel(int ID, UserLevel level) {
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(UPDATE_ACCOUNT_LEVEL_SQL)) throw query.lastError();
  // handle in-find errors
  query.addBindValue(level);
  query.addBindValue(ID);
  if (!query.exec()) throw query.lastError();
}

QList<QPair<int, int>> getActiveAccountUser() {
  QSqlQuery query;
  // handle in-server errors
  if (!query.prepare(SELECT_ALL_ACCOUNTS_ID_AND_STATES))
    throw query.lastError();
  // beacause no argument is provided we dont have to bind values for it
  if (!query.exec()) throw query.lastError();
  QList<QPair<int, int>> temp;
  while (query.next())
    temp.emplaceBack(query.value(0).toInt(), query.value(1).toInt());
  return temp;
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
  if (!query.exec()) throw query.lastError();
}

void updateUserIdentity(int ID, UserIdentity identity, const QVariant &value) {
  updateUserIdentity(ID, identity_list[identity], value);
}
