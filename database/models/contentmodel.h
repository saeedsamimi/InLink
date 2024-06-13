#ifndef CONTENTMODEL_H
#define CONTENTMODEL_H
#include <QPixmap>
#include <QString>
#include <database/models/time.h>

class ContentModel {
public:
  ContentModel(int sender_id, Time time_sent, QString content, QPixmap picture);

  /* getters */

  int getSenderID() const;
  Time getTimeSent() const;
  QString getContentText() const;
  QPixmap getContentPicture() const;

  /* setters */

  void setContentText(const QString &new_text);
  void setContentPicture(const QPixmap &new_picture);

private:
  int sender_ID;
  Time time_sent;
  QString content_text;
  QPixmap content_picture;
};

#endif // CONTENTMODEL_H
