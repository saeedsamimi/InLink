#ifndef DBINIT_H
#define DBINIT_H
#include <QtSql>
// clang-format off
const auto UPDATE_USER_IDENTITIES_SQL = QLatin1String(R"(UPDATE users SET %1 = ? WHERE ID = ?)");

const auto INSERT_USER_SQL = QLatin1String(R"(INSERT INTO users(username ,password) VALUES(?,?);)");

const auto FIND_USER_SQL = QLatin1String(R"(SELECT password FROM users WHERE username = ?;)");

const auto GET_USERS_ID_SQL = QLatin1String(R"(SELECT ID FROM users WHERE username = ?;)");

const auto ADD_ACCOUNT_SQL = QLatin1String(R"(INSERT INTO accounts(user_ID) VALUES (?);)");

const auto UPDATE_ACCOUNT_LEVEL_SQL = QLatin1String(R"(UPDATE users SET state = ? WHERE ID = ?;)");

const auto SELECT_ACCOUNTS_ID_AND_STATES = QLatin1String(R"(SELECT user_id,users.state FROM accounts INNER JOIN users ON user_id = users.ID WHERE now() - last_view < interval '30 day';)");

const auto GET_USERNAME_SQL = QLatin1String(R"(SELECT username FROM users WHERE ID = ?;)");

const auto GET_USER_ACTIVATION_LEVEL = QLatin1String(R"(SELECT state FROM users WHERE username = ?;)");
// clang-format on

void initDB();

#endif // DBINIT_H
