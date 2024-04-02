#ifndef USER_H
#define USER_H
#include <QtSql>

enum UserLevel { Added, Activated, FullyActivated };

enum UserIdentity {
  FirstName,
  LastName,
  BirthDate,
  Country,
  City,
  School,
  StartYear,
  EndYear,
  IsStudent,
  RecentJob,
  RecentCompany,
  EmploymentType
};

void insertUser(const QString &username, const QString &password);

void validateUser(const QString &username, const QString &password);

bool isUserActivated(const QString &username);

// if the active is true the user state will change to Activated othwise Added
// state will be considered!
void setUserActive(int ID, bool active);

void changeAccountLevel(int ID, UserLevel level);

int getUserID(const QString &username);

// returns the id of user
int addAccount(const QString &username);

// returns -1 if there is not any account
QList<QPair<int, int>> getActiveAccountUser();

void updateUserIdentity(int ID, const char *identity, const QVariant &value);

void updateUserIdentity(int ID, UserIdentity identity, const QVariant &value);
#endif  // USER_H
