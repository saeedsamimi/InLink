#ifndef USER_H
#define USER_H
#include <QtSql>

void insertUser(const QString &username,const QString &password);

void validateUser(const QString &username,const QString &password);

bool isUserActivated(const QString &username);

void setUserActive(int ID,bool active);

void changeAccountLevel(int ID,int level);

int getUserID(const QString& username);

// returns the id of user
int addAccount(const QString& username);

enum UserLevel{
    Added,
    Activated,
};

#endif // USER_H
