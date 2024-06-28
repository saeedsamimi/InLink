#ifndef DIRECTMESSAGE_H
#define DIRECTMESSAGE_H
#include "content.h"

class DirectMessage : public Content {
public:
  /* Constructors */

  inline DirectMessage() = default;
  DirectMessage(const QString &message_id, const QString &to_who_id,
                const QString &sender_id, const QDateTime &time_sent,
                const QString &content_text, const QString &content_picture);

  /* Getters */

  [[nodiscard]] QString getMessageID() const;
  [[nodiscard]] QString getReceiverID() const;

  /* Setters */

  void setMessageID(QString newId);
  void setReceiverID(QString newReceiverId);

private:
  QString message_id;
  QString to_who_id;
};

#endif // DIRECTMESSAGE_H
