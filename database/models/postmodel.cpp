#include "postmodel.h"

QLatin1String GET_POST_CONTENT(
    R"(SELECT content FROM posts WHERE post_id = ?;)");

QLatin1String GET_POST_PICTURE(
    R"(SELECT picture FROM posts WHERE post_id = ?)");

QLatin1String GET_POST_USER(R"(SELECT user_ID from posts WHERE post_id = ?;)");

QLatin1String GET_POST_PICTURE_EXISTENCE(
    R"(SELECT picture is not null FROM posts WHERE post_id = ?;)");
PostModel::PostModel(int postId) : post_id(postId) {}

QList<PostModel> PostModel::getAllPosts() {
  QSqlQuery query;
  if (!query.exec("SELECT post_id FROM posts;")) throw query.lastError();
  QList<PostModel> models;
  while (query.next()) models.emplace_back(query.value(0).toInt());
  return models;
}

QString PostModel::getContent() const {
  QSqlQuery query;
  if (!query.prepare(GET_POST_CONTENT)) throw query.lastError();
  query.addBindValue(post_id);
  if (query.exec()) {
    query.next();
    return query.value(0).toString();
  } else
    throw query.lastError();
}

QPixmap PostModel::getPostPixture() const {
  QSqlQuery query;
  if (!query.prepare(GET_POST_PICTURE)) throw query.lastError();
  query.addBindValue(post_id);
  if (query.exec()) {
    query.next();
    QByteArray array = query.value(0).toByteArray();
    QDataStream imageStream(&array, QIODevice::ReadOnly);
    QImage img;
    imageStream >> img;
    return QPixmap::fromImage(img);
  } else
    throw query.lastError();
}

UserModel PostModel::getUser() const {
  QSqlQuery query;
  if (!query.prepare(GET_POST_USER)) throw query.lastError();
  query.addBindValue(post_id);
  if (query.exec()) {
    query.next();
    return UserModel(query.value(0).toInt());
  }
  throw query.lastError();
}

bool PostModel::isHavePicture() const {
  QSqlQuery query;
  if (!query.prepare(GET_POST_PICTURE_EXISTENCE)) throw query.lastError();
  query.addBindValue(post_id);
  if (query.exec()) {
    query.next();
    return query.value(0).toBool();
  }
  throw query.lastError();
}
