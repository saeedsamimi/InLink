#ifndef USER_H
#define USER_H
#include <QtSql>

void insertUser(const QString &username,const QString &password);

void validateUser(const QString &username,const QString &password);

#endif // USER_H
