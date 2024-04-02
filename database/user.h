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

QString getUsername(int ID);

void validateUser(const QString &username, const QString &password);

bool isUserActivated(const QString &username);

void changeAccountLevel(int ID, UserLevel level);

int getUserID(const QString &username);

// returns the id of user
int addAccount(const QString &username);

// returns -1 if there is not any account
QPair<int, int> *getActiveAccountUser();

void updateUserIdentity(int ID, const char *identity, const QVariant &value);

void updateUserIdentity(int ID, UserIdentity identity, const QVariant &value);
#endif  // USER_H
