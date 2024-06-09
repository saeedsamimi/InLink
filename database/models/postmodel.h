#ifndef POSTMODEL_H
#define POSTMODEL_H

#include <QList>

#include "usermodel.h"

class PostModel;

class Comment {
private:
  int user_id;
  QString content;
  QDateTime commentedAt;

  Comment(int, const QString &, const QDateTime &);

public:
  QString getContent() const;
  int getUserId() const;
  QDateTime getCommentTime() const;
  friend class PostModel;
};

class PostModel {
private:
  int post_id;

public:
  PostModel(int postId);
  PostModel(const PostModel &m);
  int getPostId() const;
  static QList<PostModel> getAllPosts();
  static PostModel registerNewPost(int user_id, const QString *content,
                                   const QImage *picture);
  QString getContent() const;
  QPixmap getPostPixture() const;
  UserModel getUser() const;
  bool isHavePicture() const;
  void addLike(int user_id);
  void removeLike(int user_id);
  bool repost(int user_id);
  Comment addComment(int user_id, const QString &comment);
  QList<int> getLikes() const;
  bool isLiked(int user_id) const;
  QList<Comment> getComments() const;
};

#endif // POSTMODEL_H
