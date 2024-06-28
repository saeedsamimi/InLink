#ifndef LIKE_H
#define LIKE_H
#include <QDateTime>
#include <QString>

class Like {
public:
  /* Constructors */

  inline Like() = default;
  Like(const QString &like_id, const QString &liked_id,
       const QDateTime &time_liked);

  /* Getters */

  [[nodiscard]] QString getLikedId() const;
  [[nodiscard]] QString getWhoLikedId() const;
  [[nodiscard]] QDateTime getTimeLiked() const;

  /* Setters */

  void setLikedId(const QString &newID);
  void setWhoLikedId(const QString &newID);
  void setTimeLiked(const QDateTime &newTime);

private:
  QString like_id;
  QString liked_id;
  QDateTime time_liked;
};

#endif // LIKE_H
