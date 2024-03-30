#ifndef DBINIT_H
#define DBINIT_H

#include <QtSql>
#include <database/encryption.h>

const auto USERS_SQL = QLatin1String(R"(
    CREATE TABLE IF NOT EXISTS users(
        ID INTEGER PRIMARY KEY AUTOINCREMENT,
        username VARCHAR(30) UNIQUE NOT NULL,
        password VARCHAR(64) NOT NULL
    );
)");

const auto INSERT_USER_SQL = QLatin1String(R"(
    INSERT INTO users(username ,password) VALUES(?,?);
)");

const auto FIND_USER_SQL = QLatin1String(R"(
    SELECT password FROM users WHERE username = ?;
)");

void insertUser(const QString &username,const QString &password){
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

void validateUser(const QString &username,const QString &password){
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
            throw QObject::tr("This password is incorrect!");
    }
    else{// throw error if the user is not exists
        throw QObject::tr("This user is not exist, please sign in!");
    }
}

QSqlError initDB(){
    // create connection and try to connect
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("InLink");
    if(!db.open())
        return db.lastError();
    // run the query for create table if not exist
    QSqlQuery query;
    if(!query.exec(USERS_SQL))
        return query.lastError();
    // return empty error
    return QSqlError();
}


#endif // DBINIT_H
