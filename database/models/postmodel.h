#ifndef POSTMODEL_H
#define POSTMODEL_H

#include <QDateTime>
#include <QImage>
#include <QList>
#include <QPixmap>

class PostModel;
class UserModel;

class Comment {
private:
  int user_id;
  QString content;
  QDateTime commentedAt;

  /* private constructor */

  Comment(int, const QString &, const QDateTime &);

public:
  /* only have getters */

  QString getContent() const;
  int getUserId() const;
  QDateTime getCommentTime() const;

  /* define class PostModel as a friend class */

  friend class PostModel;
};

class PostModel {
private:
  int post_id;
  int reposted_from;
  bool suggested;

public:
  /* Constructors */

  PostModel(int postId, int reposted_from = -1, bool suggested = false);
  PostModel(const PostModel &m);

  /* static object creators */

  static PostModel registerNewPost(int user_id, const QString *content,
                                   const QImage *picture);

  /* static function to get all posts */

  static QList<PostModel> getLastTenPosts(int count = 10);
  static QList<PostModel> getRelativePosts(int user_id);
  static QList<PostModel> getFollowedPosts(int user_id);

  /* Post Model getters */

  int getPostId() const;
  QString getContent() const;
  QPixmap getPostPixture() const;
  UserModel getUser() const;
  bool isHavePicture() const;
  QDateTime getPostedAtTime() const;
  bool isSuggested() const;

  /* Post Model like functions */

  void addLike(int user_id);
  void removeLike(int user_id);
  QList<int> getLikes() const;
  bool isLiked(int user_id) const;

  /* Post Model repost functions */

  bool isReposted() const;
  PostModel repost(int user_id);

  /* Post Model Comment functions */

  Comment addComment(int user_id, const QString &comment);
  QList<Comment> getComments() const;

  friend class UserModel;
};

#include <database/models/usermodel.h>

#endif // POSTMODEL_H
