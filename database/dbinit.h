#ifndef DBINIT_H
#define DBINIT_H
#include <QtSql>

const auto USERS_SQL = QLatin1String(R"(
CREATE TABLE IF NOT EXISTS users(
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    username VARCHAR(30) UNIQUE NOT NULL,
    password VARCHAR(64) NOT NULL,
    first_name TEXT,last_name TEXT,birth_date VARCHAR(8),
    country TEXT, city TEXT,
    school TEXT,start_year INTEGER,end_year INTEGER,is_student INTEGER,
    recent_job TEXT,emp_type TEXT,recent_company TEXT
);)");

const auto ACCOUNTS_SQL = QLatin1String(R"(
CREATE TABLE IF NOT EXISTS accounts(
    account_ID INTEGER PRIMARY KEY AUTOINCREMENT,
    user_ID INTEGER NOT NULL UNIQUE,
    last_view TEXT NOT NULL,
    state INTEGER DEFAULT 0,
    profile BOLB DEFAULT NULL,
    bio TEXT DEFAULT "Unknown",
    abilities TEXT
);)");

const auto POSTS_SQL = QLatin1String(R"(
CREATE TABLE posts(
    post_id INTEGER not null primary key autoincrement,
    user_id INTEGER not null,
    picture BLOB null,
    content TEXT not null,
    created_at DATETIME not null default CURRENT_TIMESTAMP
);)");

const auto UPDATE_USER_IDENTITIES_SQL = QLatin1String(R"(
    UPDATE users SET %1 = ? WHERE ID = ?
)");

const auto INSERT_USER_SQL = QLatin1String(R"(
    INSERT INTO users(username ,password) VALUES(?,?);
)");

const auto FIND_USER_SQL = QLatin1String(R"(
    SELECT password FROM users WHERE username = ?;
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

const auto SELECT_ACCOUNTS_ID_AND_STATES = QLatin1String(R"(
    SELECT user_ID,state FROM accounts WHERE strftime('%s', last_view) > strftime('%s', datetime('now','localtime','-1 month')) LIMIT 1;
)");

const auto GET_USERNAME_SQL = QLatin1String(R"(
    SELECT username FROM users WHERE ID = ?;
)");

QSqlError initDB();

#endif  // DBINIT_H
