#include "user.h"
#include "dbinit.h"
#include "encryption.h"

void insertUser(const QString &username, const QString &password){
    QSqlQuery query;
    // handle in-server errors
    if(!query.prepare(INSERT_USER_SQL))
        throw query.lastError();
    // handle in-insert errors
    query.addBindValue(username);
    query.addBindValue(hashUsingSHA256(password));
    // error codes:
    //        2067:
    //            the user is already exists!
    if(!query.exec())
        if(query.lastError().nativeErrorCode().toInt() == 2067)
            throw QObject::tr("This username already exists!");
        else
            throw query.lastError();
}

void validateUser(const QString &username, const QString &password){
    QSqlQuery query;
    // handle in-server errors
    if(!query.prepare(FIND_USER_SQL))
        throw query.lastError();
    // handle in-find errors
    query.addBindValue(username);
    // no error code is provided
    if(!query.exec())
        throw query.lastError();
    if(query.next()){
        // returns if the user password correct otherwise gives an exception
        if(query.value(0).toString() != hashUsingSHA256(password))
            throw QPair<QString,bool>(QObject::tr("This password is incorrect!"),false);
    }
    else{// throw error if the user is not exists
        throw QPair<QString,bool>(QObject::tr("This user is not exist, do you want to sign in?"),true);
    }
}
