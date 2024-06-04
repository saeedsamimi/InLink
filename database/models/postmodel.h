#ifndef POSTMODEL_H
#define POSTMODEL_H

#include <QList>

#include "usermodel.h"

class PostModel {
private:
  int post_id;

public:
  PostModel(int postId);
  PostModel(const PostModel &m);
  static QList<PostModel> getAllPosts();
  static PostModel registerNewPost(int user_id, const QString *content,
                                   const QImage *picture);
  QString getContent() const;
  QPixmap getPostPixture() const;
  UserModel getUser() const;
  bool isHavePicture() const;
};

#endif // POSTMODEL_H
