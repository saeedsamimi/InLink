#ifndef COMMENT_SCHEMA_H
#define COMMENT_SCHEMA_H
#include "content.h"

class Comment : public Content {
public:
  /* Constructors */

  inline Comment() = default;
  Comment(const QString &comment_id, const QString &receiver_id,
          const QString &sender_id, const QDateTime &time_sent,
          const QString &content_text, const QString &content_picture);

  /* Getters */

  [[nodiscard]] QString getCommentID();
  [[nodiscard]] QString getReceiverID();

  /* Setters */

  void setCommentId(QString newCommentID);
  void setReceiverId(QString newReceiverID);

private:
  QString comment_id;
  QString receiver_id;
};

#endif // COMMENT_SCHEMA_H
