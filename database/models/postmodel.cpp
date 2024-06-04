#include "postmodel.h"

// clang-format off
QLatin1String GET_POST_CONTENT(R"(SELECT content FROM posts WHERE post_id = ?;)");

QLatin1String GET_POST_PICTURE(R"(SELECT picture FROM posts WHERE post_id = ?)");

QLatin1String GET_POST_USER(R"(SELECT user_ID from posts WHERE post_id = ?;)");

QLatin1String GET_POST_PICTURE_EXISTENCE(R"(SELECT picture is not null FROM posts WHERE post_id = ?;)");

QLatin1String CREATE_POST(R"(INSERT INTO posts(user_ID,picture,content) VALUES (?,?,?);)");
// clang-format on

PostModel::PostModel(int postId) : post_id(postId) {}

PostModel::PostModel(const PostModel &m) : post_id(m.post_id) {}

QList<PostModel> PostModel::getAllPosts() {
  QSqlQuery query;
  if (!query.exec("SELECT post_id FROM posts;"))
    throw query.lastError();
  QList<PostModel> models;
  while (query.next())
    models.emplace_back(query.value(0).toInt());
  return models;
}

PostModel PostModel::registerNewPost(int user_id, const QString *content,
                                     const QImage *picture) {
  QSqlQuery query;
  if (!query.prepare(CREATE_POST))
    throw query.lastError();
  query.addBindValue(user_id);
  QByteArray buff;
  if (picture != nullptr) {
    QDataStream stream(&buff, QIODevice::WriteOnly);
    stream << *picture;
    query.addBindValue(buff);
  } else /*bind null value in the database*/
    query.addBindValue(buff);
  query.addBindValue(*content);
  if (query.exec())
    return PostModel(query.lastInsertId().toInt());
  throw query.lastError();
}

QString PostModel::getContent() const {
  QSqlQuery query;
  if (!query.prepare(GET_POST_CONTENT))
    throw query.lastError();
  query.addBindValue(post_id);
  if (query.exec()) {
    query.next();
    return query.value(0).toString();
  } else
    throw query.lastError();
}

QPixmap PostModel::getPostPixture() const {
  QSqlQuery query;
  if (!query.prepare(GET_POST_PICTURE))
    throw query.lastError();
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
  if (!query.prepare(GET_POST_USER))
    throw query.lastError();
  query.addBindValue(post_id);
  if (query.exec()) {
    query.next();
    return UserModel(query.value(0).toInt());
  }
  throw query.lastError();
}

bool PostModel::isHavePicture() const {
  QSqlQuery query;
  if (!query.prepare(GET_POST_PICTURE_EXISTENCE))
    throw query.lastError();
  query.addBindValue(post_id);
  if (query.exec()) {
    query.next();
    return query.value(0).toBool();
  }
  throw query.lastError();
}
