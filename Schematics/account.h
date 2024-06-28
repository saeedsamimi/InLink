#ifndef ACCOUNT_SCHEMA_H
#define ACCOUNT_SCHEMA_H
#include "directmessage.h"
#include "post.h"
#include <QList>
#include <QString>

class Account {
public:
  /* Constructors */

  inline Account() = default;
  Account(const QString &account_id, const QString &phone_number,
          const QString &email);

  /* Getters */

  [[nodiscard]] QString getAccount() const;
  [[nodiscard]] QString getPhoneNumber() const;
  [[nodiscard]] QString getEmail() const;
  [[nodiscard]] QList<Account *> &getConnections();
  [[nodiscard]] QList<Account *> &getFollowings();
  [[nodiscard]] QList<Post> &getAllPosts();
  [[nodiscard]] QList<DirectMessage> &getAllMessages();

private:
  QString account_id;
  QString phone_number;
  QString email;
  QList<Account *> Connection;
  QList<Account *> following;
  QList<Post> posts;
  QList<DirectMessage> messages;
};

#endif // ACCOUNT_SCHEMA_H
