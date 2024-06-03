#ifndef POSTMODEL_H
#define POSTMODEL_H

#include <QList>

#include "usermodel.h"

class PostModel {
 private:
  int post_id;

 public:
  PostModel(int postId);
  static QList<PostModel> getAllPosts();
  QString getContent() const;
  QPixmap getPostPixture() const;
  UserModel getUser() const;
  bool isHavePicture() const;
};

#endif  // POSTMODEL_H
