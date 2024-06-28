#ifndef CONTENT_H
#define CONTENT_H
#include <QDateTime>
#include <QPixmap>
#include <QString>

class Content {
public:
  /* Constructors */

  inline Content() = default;
  Content(QString sender_ID, QDateTime time_sent, QString content_text,
          QPixmap picture);

  /* Getters */

  [[nodiscard]] QString getSenderId() const;
  [[nodiscard]] QDateTime getTimeSent() const;
  [[nodiscard]] QString getContentText() const;
  [[nodiscard]] QPixmap getContentPicture() const;

  /* Setters */

  void setSenderId(const QString &text);
  void setTimeSent(const QDateTime &time);
  void setContentText(const QString &content);
  void setContentPicture(const QPixmap &pic);

protected:
  QString sender_ID;
  QDateTime time_sent;
  QString content_text;
  QPixmap content_picture;
};

#endif // CONTENT_H
