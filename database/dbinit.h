#ifndef DBINIT_H
#define DBINIT_H
#include <QtSql>

const auto USERS_SQL  = QLatin1String(R"(
    CREATE TABLE IF NOT EXISTS users(
        ID INTEGER PRIMARY KEY AUTOINCREMENT,
        username VARCHAR(30) UNIQUE NOT NULL,
        password VARCHAR(64) NOT NULL,
        activated INTEGER DEFAULT 0
    );
)");

const auto ACCOUNTS_SQL = QLatin1String(R"(
    CREATE TABLE IF NOT EXISTS accounts(
        account_ID INTEGER PRIMARY KEY AUTOINCREMENT,
        user_ID INTEGER NOT NULL UNIQUE,
        last_view TEXT NOT NULL,
        state INTEGER DEFAULT 0
    );
)");

const auto INSERT_USER_SQL = QLatin1String(R"(
    INSERT INTO users(username ,password) VALUES(?,?);
)");

const auto FIND_USER_SQL = QLatin1String(R"(
    SELECT password FROM users WHERE username = ?;
)");

const auto FIND_USER_ACTIVATION_SQL = QLatin1String(R"(
    SELECT activated FROM users WHERE username = ?;
)");

const auto UPDATE_USER_ACTIVATION_SQL = QLatin1String(R"(
    UPDATE users SET activated = ? WHERE ID = ?;
)");

const auto GET_USERS_ID_SQL = QLatin1String(R"(
    SELECT ID FROM users WHERE username = ?;
)");

const auto ADD_ACCOUNT_SQL = QLatin1String(R"(
    INSERT INTO accounts(user_ID,last_view) VALUES (?,datetime('now','localtime'));
)");

const auto UPDATE_ACCOUNT_LEVEL_SQL = QLatin1String(R"(
    UPDATE accounts SET state = ? WHERE user_ID = ?;
)");

QSqlError initDB();

#endif //DBINIT_H
