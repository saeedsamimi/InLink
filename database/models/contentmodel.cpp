#include "contentmodel.h"

ContentModel::ContentModel(int sender_id, Time time_sent, QString content,
                           QPixmap picture)
    : sender_ID(sender_id), time_sent(time_sent), content_text(content),
      content_picture(picture) {}

int ContentModel::getSenderID() const { return sender_ID; }

Time ContentModel::getTimeSent() const { return time_sent; }

QString ContentModel::getContentText() const { return content_text; }

QPixmap ContentModel::getContentPicture() const { return content_picture; }

void ContentModel::setContentText(const QString &new_text) {
  content_text = new_text;
}

void ContentModel::setContentPicture(const QPixmap &new_picture) {
  content_picture = new_picture;
}
