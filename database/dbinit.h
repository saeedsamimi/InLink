#ifndef DBINIT_H
#define DBINIT_H
#include <QtSql>

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

QSqlError initDB();

#endif //DBINIT_H
