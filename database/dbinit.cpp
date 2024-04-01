#include "dbinit.h"

QSqlError initDB(){
    // create connection and try to connect
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("InLink.db");
    if(!db.open())
        return db.lastError();
    // run the query for create table if not exist
    QSqlQuery query;
    if(!query.exec(USERS_SQL))
        return query.lastError();
    if(!query.exec(ACCOUNTS_SQL))
        return query.lastError();
    // return empty error
    return QSqlError();
}
