#include "postmodel.h"

// clang-format off
const QLatin1String GET_POST_CONTENT(R"(SELECT content FROM posts WHERE post_id = ?)");

const QLatin1String GET_POST_PICTURE(R"(SELECT picture FROM posts WHERE post_id = ?)");

const QLatin1String GET_POST_USER(R"(SELECT user_ID FROM posts WHERE post_id = ?)");

const QLatin1String GET_POST_PICTURE_EXISTENCE(R"(SELECT length(picture) != 0 FROM posts WHERE post_id = ?)");

const QLatin1String CREATE_POST(R"(INSERT INTO posts(user_ID,picture,content) VALUES (?,?,?))");

const QLatin1String POST_ADD_LIKE(R"(INSERT INTO likes (post_id,user_id) VALUES (?,?))");

const QLatin1String POST_ADD_COMMENT(R"(INSERT INTO comments (post_id, user_id, content) VALUES (?,?,?))");

const QLatin1String GET_POST_ALL_LIKES(R"(SELECT user_id FROM likes WHERE post_id = ?)");

const QLatin1String GET_POST_LIKE_FOR_SPECIFIC_USER(R"(SELECT count(*) FROM likes WHERE post_id = ? AND user_id = ?)");

const QLatin1String GET_POST_ALL_COMMENTS(R"(SELECT user_id,content,commented_at FROM comments WHERE post_id = ?)");

const QLatin1String POST_REMOVE_LIKE(R"(DELETE FROM likes WHERE post_id = ? AND user_id = ?)");

const QLatin1String POST_REGISTER_REPOST(R"(INSERT INTO reposts(user_id,post_id) VALUES(?,?))");
// clang-format on

PostModel::PostModel(int postId) : post_id(postId) {}

PostModel::PostModel(const PostModel &m) : post_id(m.post_id) {}

int PostModel::getPostId() const { return post_id; }

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
  query.prepare(CREATE_POST);
  query.addBindValue(user_id);
  QByteArray buff;
  if (picture != nullptr) {
    QBuffer buffer(&buff);
    picture->save(&buffer, "PNG");
    query.addBindValue(buff.toBase64());
  } else /*bind null value in the database*/
    query.addBindValue(buff.toBase64());
  query.addBindValue(*content);
  if (query.exec())
    return PostModel(query.lastInsertId().toInt());
  qDebug() << query.lastError();
  throw query.lastError();
}

QString PostModel::getContent() const {
  QSqlQuery query;
  query.prepare(GET_POST_CONTENT);
  query.addBindValue(post_id);
  if (query.exec()) {
    query.next();
    return query.value(0).toString();
  } else
    throw query.lastError();
}

QPixmap PostModel::getPostPixture() const {
  QSqlQuery query;
  query.prepare(GET_POST_PICTURE);
  query.addBindValue(post_id);
  if (query.exec()) {
    query.next();
    QByteArray array = QByteArray::fromBase64(query.value(0).toByteArray());
    QBuffer buff(&array);
    QImage img;
    img.load(&buff, "PNG");
    return QPixmap::fromImage(img);
  } else
    throw query.lastError();
}

UserModel PostModel::getUser() const {
  QSqlQuery query;
  query.prepare(GET_POST_USER);
  query.addBindValue(post_id);
  if (query.exec()) {
    query.next();
    return UserModel(query.value(0).toInt());
  }
  throw query.lastError();
}

bool PostModel::isHavePicture() const {
  QSqlQuery query;
  query.prepare(GET_POST_PICTURE_EXISTENCE);
  query.addBindValue(post_id);
  if (query.exec()) {
    query.next();
    return query.value(0).toBool();
  }
  throw query.lastError();
}

void PostModel::addLike(int user_id) {
  QSqlQuery query;
  query.prepare(POST_ADD_LIKE);
  query.addBindValue(post_id);
  query.addBindValue(user_id);
  if (!query.exec())
    throw query.lastError();
}

void PostModel::removeLike(int user_id) {
  QSqlQuery query;
  query.prepare(POST_REMOVE_LIKE);
  query.addBindValue(post_id);
  query.addBindValue(user_id);
  if (!query.exec())
    throw query.lastError();
}

bool PostModel::repost(int user_id) {
  QSqlQuery query;
  query.prepare(POST_REGISTER_REPOST);
  query.addBindValue(user_id);
  query.addBindValue(post_id);
  if (!query.exec()) {
    if (query.lastError().nativeErrorCode() == "23505")
      return false;
    throw query.lastError();
  }
  return true;
}

Comment PostModel::addComment(int user_id, const QString &comment) {
  QSqlQuery query;
  query.prepare(POST_ADD_COMMENT);
  query.addBindValue(post_id);
  query.addBindValue(user_id);
  query.addBindValue(comment);
  if (!query.exec())
    throw query.lastError();
  return Comment(user_id, comment, QDateTime::currentDateTime());
}

QList<int> PostModel::getLikes() const {
  QSqlQuery query;
  query.prepare(GET_POST_ALL_LIKES);
  query.addBindValue(post_id);
  if (!query.exec())
    throw query.lastError();
  QList<int> likes_temp;
  while (query.next())
    likes_temp.append(query.value(0).toInt());
  return likes_temp;
}

bool PostModel::isLiked(int user_id) const {
  QSqlQuery query;
  query.prepare(GET_POST_LIKE_FOR_SPECIFIC_USER);
  query.addBindValue(post_id);
  query.addBindValue(user_id);
  if (!query.exec())
    throw query.lastError();
  query.next();
  return query.value(0).toBool();
}

QList<Comment> PostModel::getComments() const {
  QSqlQuery query;
  query.prepare(GET_POST_ALL_COMMENTS);
  query.addBindValue(post_id);
  if (!query.exec())
    throw query.lastError();
  QList<Comment> comments_temp;
  while (query.next())
    comments_temp.push_back(Comment(query.value(0).toInt(),
                                    query.value(1).toString(),
                                    query.value(2).toDateTime()));
  return comments_temp;
}

Comment::Comment(int id, const QString &comment, const QDateTime &time)
    : user_id(id), content(comment), commentedAt(time) {}

QString Comment::getContent() const { return content; }

int Comment::getUserId() const { return user_id; }

QDateTime Comment::getCommentTime() const { return commentedAt; }
