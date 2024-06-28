#ifndef POST_H
#define POST_H
#include "comment.h"
#include "content.h"
#include "like.h"

class Post : public Content {
public:
  /* Constructors */

  inline Post() = default;
  Post(const Post &) = default;
  Post(const QString &post_id, const QString &sender_id,
       const QDateTime &time_sent, const QString &content_text,
       const QString &content_picture);

  /* Getters */

  [[nodiscard]] QList<Comment> getComments() const;
  [[nodiscard]] QList<Like> getLikes() const;

  /* Setters */

  void addComment(const Comment &newComment);
  void addLike(const Like &newLike);
  void removeLike(const QString &like_id);

  /* Static methods */

  static Post repost(const QString &user_id, Post &post);

private:
  QString post_id;
  size_t repost_counter;
  QList<Comment> comments;
  QList<Like> likes;
};

#endif // POST_H
