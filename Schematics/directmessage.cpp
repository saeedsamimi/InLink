#include "directmessage.h"

DirectMessage::DirectMessage(const QString &message_id,
                             const QString &to_who_id, const QString &sender_id,
                             const QDateTime &time_sent,
                             const QString &content_text,
                             const QString &content_picture)
    : message_id(message_id), to_who_id(to_who_id),
      Content(sender_id, time_sent, content_text, content_picture) {}

QString DirectMessage::getMessageID() const { return message_id; }

QString DirectMessage::getReceiverID() const { return to_who_id; }

void DirectMessage::setMessageID(QString newId) { message_id = newId; }

void DirectMessage::setReceiverID(QString newReceiverId) {
  to_who_id = newReceiverId;
}
