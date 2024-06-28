#include "account.h"

Account::Account(const QString &account_id, const QString &phone_number,
                 const QString &email)
    : account_id(account_id), phone_number(phone_number), email(email) {}

QString Account::getAccount() const { return account_id; }

QString Account::getPhoneNumber() const { return phone_number; }

QString Account::getEmail() const { return email; }

QList<Account *> &Account::getConnections() { return Connection; }

QList<Account *> &Account::getFollowings() { return following; }

QList<Post> &Account::getAllPosts() { return posts; }

QList<DirectMessage> &Account::getAllMessages() { return messages; }
