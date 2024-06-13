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

int validateUser(const QString &username, const QString &password);

int getUserActivationLevel(const QString &username);

void changeAccountLevel(int ID, UserLevel level);

int getUserID(const QString &username);

// returns the id of user
int addAccount(const QString &username, const QString &password);

bool getActiveAccountUser(int &, int &);

void updateUserIdentity(int ID, const char *identity, const QVariant &value);

void updateUserIdentity(int ID, UserIdentity identity, const QVariant &value);
#endif // USER_H
