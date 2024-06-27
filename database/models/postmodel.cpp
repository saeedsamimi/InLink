#include "postmodel.h"
#include <utils/Util.h>

// clang-format off
const QLatin1String GET_LAST_TEN_POSTS(R"(SELECT post_id,posted_from FROM posts ORDER BY created_at DESC LIMIT ?)");

const QLatin1String GET_MOST_RELATIVE_POSTS(R"(SELECT p.post_id,p.posted_from FROM posts p JOIN users u ON p.user_id = u.id JOIN jobs j ON u.recent_job = j.job_name JOIN users target_user ON target_user.id = :id JOIN jobs target_job ON target_user.recent_job = target_job.job_name WHERE p.user_id != :id AND ( j.job_group_id = target_job.job_group_id OR u.city = target_user.city OR u.country = target_user.country) ORDER BY created_at DESC)");

const QLatin1String GET_MOST_FOLLOWED_POSTS(R"(SELECT p.post_id,p.posted_from FROM posts p JOIN users u ON p.user_id = u.id JOIN follow f ON f.following = u.id WHERE p.user_id != :id AND f.follower = :id AND f.following_state = TRUE ORDER BY created_at DESC)");

const QLatin1String GET_POST_CONTENT(R"(SELECT content FROM posts WHERE post_id = ?)");

const QLatin1String GET_POST_PICTURE(R"(SELECT picture FROM posts WHERE post_id = ?)");

const QLatin1String GET_POST_USER(R"(SELECT user_ID FROM posts WHERE post_id = ?)");

const QLatin1String GET_POST_PICTURE_EXISTENCE(R"(SELECT length(picture) != 0 FROM posts WHERE post_id = ?)");

const QLatin1String GET_POST_TIME_POST(R"(SELECT created_at FROM posts WHERE post_id = ?)");

const QLatin1String CREATE_POST(R"(INSERT INTO posts(user_ID,picture,content) VALUES (?,?,?))");

const QLatin1String POST_ADD_LIKE(R"(INSERT INTO likes (post_id,user_id) VALUES (?,?))");

const QLatin1String POST_ADD_COMMENT(R"(INSERT INTO comments (post_id, user_id, content) VALUES (?,?,?))");

const QLatin1String GET_POST_ALL_LIKES(R"(SELECT user_id FROM likes WHERE post_id = ?)");

const QLatin1String GET_POST_LIKE_FOR_SPECIFIC_USER(R"(SELECT count(*) FROM likes WHERE post_id = ? AND user_id = ?)");

const QLatin1String GET_POST_ALL_COMMENTS(R"(SELECT user_id,content,commented_at FROM comments WHERE post_id = ?)");

const QLatin1String POST_REMOVE_LIKE(R"(DELETE FROM likes WHERE post_id = ? AND user_id = ?)");

const QLatin1String POST_REGISTER_REPOST(R"(INSERT INTO posts(user_id,posted_from) VALUES(?,?))");
// clang-format on

PostModel::PostModel(int postId, int reposted_from, bool is_suggested)
    : post_id(postId), reposted_from(reposted_from), suggested(is_suggested) {}

PostModel::PostModel(const PostModel &m)
    : post_id(m.post_id), reposted_from(m.reposted_from),
      suggested(m.suggested) {}

int PostModel::getPostId() const {
  return isReposted() ? PostModel(reposted_from).getPostId() : post_id;
}

QList<PostModel> PostModel::getLastTenPosts(int count) {
  CREATE_SQL(GET_LAST_TEN_POSTS);
  SQL_BIND(count);
  if (!query.exec())
    SQL_THROW;
  QList<PostModel> models;
  while (query.next())
    models.emplace_back(query.value(0).toInt(),
                        query.value(1).isNull() ? -1 : query.value(1).toInt());
  return models;
}

QList<PostModel> PostModel::getRelativePosts(int user_id) {
  CREATE_SQL(GET_MOST_RELATIVE_POSTS);
  SQL_BIND_PLACED(":id", user_id);
  if (!query.exec())
    SQL_THROW;
  QList<PostModel> posts;
  while (query.next())
    posts.emplace_back(query.value(0).toInt(),
                       query.value(1).isNull() ? -1 : query.value(1).toInt(),
                       true);
  return posts;
}

QList<PostModel> PostModel::getFollowedPosts(int user_id) {
  CREATE_SQL(GET_MOST_FOLLOWED_POSTS);
  SQL_BIND_PLACED(":id", user_id);
  if (!query.exec())
    SQL_THROW;
  QList<PostModel> posts;
  while (query.next())
    posts.emplace_back(query.value(0).toInt(),
                       query.value(1).isNull() ? -1 : query.value(1).toInt());
  return posts;
}

PostModel PostModel::registerNewPost(int user_id, const QString *content,
                                     const QImage *picture) {
  CREATE_SQL(CREATE_POST);
  SQL_BIND(user_id);
  QByteArray buff;
  if (picture != nullptr) {
    QBuffer buffer(&buff);
    picture->save(&buffer, "PNG");
  }
  SQL_BIND(buff.toBase64());
  SQL_BIND(*content);
  if (query.exec())
    return PostModel(query.lastInsertId().toInt());
  SQL_THROW;
}

QString PostModel::getContent() const {
  CREATE_SQL(GET_POST_CONTENT);
  SQL_BIND(getPostId());
  if (query.exec()) {
    query.next();
    return query.value(0).toString();
  }
  SQL_THROW;
}

QPixmap PostModel::getPostPixture() const {
  CREATE_SQL(GET_POST_PICTURE);
  SQL_BIND(getPostId());
  if (query.exec()) {
    query.next();
    QByteArray array = QByteArray::fromBase64(query.value(0).toByteArray());
    QBuffer buff(&array);
    QImage img;
    img.load(&buff, "PNG");
    return QPixmap::fromImage(img);
  }
  SQL_THROW;
}

UserModel PostModel::getUser() const {
  CREATE_SQL(GET_POST_USER);
  SQL_BIND(post_id);
  if (query.exec()) {
    query.next();
    return UserModel(query.value(0).toInt());
  }
  SQL_THROW;
}

bool PostModel::isHavePicture() const {
  CREATE_SQL(GET_POST_PICTURE_EXISTENCE);
  SQL_BIND(getPostId());
  if (query.exec()) {
    query.next();
    return query.value(0).toBool();
  }
  SQL_THROW;
}

QDateTime PostModel::getPostedAtTime() const {
  CREATE_SQL(GET_POST_TIME_POST);
  SQL_BIND(post_id);
  if (query.exec()) {
    query.next();
    return query.value(0).toDateTime();
  }
  SQL_THROW;
}

bool PostModel::isSuggested() const { return suggested; }

void PostModel::addLike(int user_id) {
  CREATE_SQL(POST_ADD_LIKE);
  SQL_BIND(post_id);
  SQL_BIND(user_id);
  if (!query.exec())
    SQL_THROW;
}

void PostModel::removeLike(int user_id) {
  CREATE_SQL(POST_REMOVE_LIKE);
  SQL_BIND(post_id);
  SQL_BIND(user_id);
  if (!query.exec())
    SQL_THROW;
}

PostModel PostModel::repost(int user_id) {
  int root_post_id = getPostId();
  CREATE_SQL(POST_REGISTER_REPOST);
  SQL_BIND(user_id);
  SQL_BIND(root_post_id);
  if (!query.exec())
    SQL_THROW;
  return PostModel(query.lastInsertId().toInt(), root_post_id);
}

Comment PostModel::addComment(int user_id, const QString &comment) {
  CREATE_SQL(POST_ADD_COMMENT);
  SQL_BIND(post_id);
  SQL_BIND(user_id);
  SQL_BIND(comment);
  if (!query.exec())
    SQL_THROW;
  return Comment(user_id, comment, QDateTime::currentDateTime());
}

QList<int> PostModel::getLikes() const {
  CREATE_SQL(GET_POST_ALL_LIKES);
  SQL_BIND(post_id);
  if (!query.exec())
    SQL_THROW;
  QList<int> likes_temp;
  while (query.next())
    likes_temp.append(query.value(0).toInt());
  return likes_temp;
}

bool PostModel::isLiked(int user_id) const {
  CREATE_SQL(GET_POST_LIKE_FOR_SPECIFIC_USER);
  SQL_BIND(post_id);
  SQL_BIND(user_id);
  if (!query.exec())
    SQL_THROW;
  query.next();
  return query.value(0).toBool();
}

bool PostModel::isReposted() const { return reposted_from >= 0; }

QList<Comment> PostModel::getComments() const {
  CREATE_SQL(GET_POST_ALL_COMMENTS);
  SQL_BIND(post_id);
  if (!query.exec())
    SQL_THROW;
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
