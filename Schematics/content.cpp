#include "content.h"

Content::Content(QString sender_ID, QDateTime time_sent, QString content_text,
                 QPixmap picture)
    : sender_ID(sender_ID), time_sent(time_sent), content_text(content_text),
      content_picture(picture) {}

QString Content::getSenderId() const { return sender_ID; }

QDateTime Content::getTimeSent() const { return time_sent; }

QString Content::getContentText() const { return content_text; }

QPixmap Content::getContentPicture() const { return content_picture; }

void Content::setSenderId(const QString &text) { sender_ID = text; }

void Content::setTimeSent(const QDateTime &time) { time_sent = time; }

void Content::setContentText(const QString &content) { content_text = content; }

void Content::setContentPicture(const QPixmap &pic) { content_picture = pic; }
