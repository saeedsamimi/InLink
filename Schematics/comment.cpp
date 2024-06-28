#include "comment.h"

Comment::Comment(const QString &comment_id, const QString &receiver_id,
                 const QString &sender_id, const QDateTime &time_sent,
                 const QString &content_text, const QString &content_picture)
    : comment_id(comment_id), receiver_id(receiver_id),
      Content(sender_id, time_sent, content_text, content_picture) {}

QString Comment::getCommentID() { return comment_id; }

QString Comment::getReceiverID() { return receiver_id; }

void Comment::setCommentId(QString newCommentID) { comment_id = newCommentID; }

void Comment::setReceiverId(QString newReceiverID) {
  receiver_id = newReceiverID;
}
