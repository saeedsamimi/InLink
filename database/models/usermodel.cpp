#include "usermodel.h"

#include <QSqlQuery>
#include <QVariant>
#include <database/encryption.hpp>
#include <utils/Util.h>

// clang-format off
const QLatin1String LOAD_USER_SQL(R"(SELECT username,first_name,last_name,emp_type,iscompany FROM users WHERE ID = ?)");

const QLatin1String GET_USER_PROFILE_PICTURE_EXISTENCE(R"(SELECT profile IS NOT NULL FROM users WHERE ID = ?)");

const QLatin1String GET_USER_PROFILE_PICTURE(R"(SELECT profile FROM users WHERE ID = ?)");

const QLatin1String UPDATE_USER_PROFILE_PICTURE(R"(UPDATE users SET profile = ? WHERE ID = ?)");

const QLatin1String DELETE_USER_PROFILE_PICTURE(R"(UPDATE users SET profile = null WHERE ID = ?)");

const QLatin1String GET_USER_BIOGRAPHY(R"(SELECT bio FROM users WHERE ID = ?)");

const QLatin1String UPDATE_USER_BIOGRAPHY(R"(UPDATE users SET bio = ? WHERE ID = ?)");

const QLatin1String GET_USER_ABILITIES(R"(SELECT abilities FROM users WHERE ID = ?)");

const QLatin1String UPDATE_USER_ABILITIES(R"(UPDATE users SET abilities = ? WHERE ID = ?)");

const QLatin1String GET_USER_JOB(R"(SELECT recent_job FROM users WHERE id = ?)");

const QLatin1String LOGOUT_USER(R"(DELETE FROM accounts WHERE user_ID = ?)");

const QLatin1String FOLLOW_USER(R"(INSERT INTO follow VALUES (:follower,:following))");

const QLatin1String IS_FOLLOWING_USER(R"(SELECT following_state FROM follow WHERE follower = :follower AND following = :following)");

const QLatin1String GET_ALL_PENDING_INVITATIONS(R"(SELECT follower,following_state IS null FROM follow where following = ? AND (following_state is null OR following_state = false);)");

const QLatin1String SET_INVITATION_STATUS(R"(UPDATE follow SET following_state = :state WHERE follower = :follower AND following = :following;)");

const QLatin1String UNFOLLOW_USER(R"(DELETE FROM follow WHERE follower = :follower AND following = :following)");

const QLatin1String GET_USER_POSTS(R"(SELECT post_id,posted_from FROM posts WHERE user_id = ?)");

const QLatin1String SIGN_UP_AS_COMPANY(R"(UPDATE users SET iscompany = TRUE WHERE id = ?)");

const QLatin1String GET_RELATED_USERS(
R"(WITH TargetUserJobGroup AS (SELECT j.job_group_id FROM users u JOIN jobs j ON j.job_name = u.recent_job WHERE u.id = :id),
RelatedUsers AS (SELECT u.id FROM users u JOIN jobs j ON j.job_name = u.recent_job WHERE j.job_group_id = (SELECT job_group_id FROM TargetUserJobGroup) AND u.id != :id),
FollowedUsers AS (SELECT f.following FROM follow f WHERE f.follower = :id)
SELECT r.id FROM RelatedUsers r WHERE r.id NOT IN (SELECT following FROM FollowedUsers);)"
);

const QLatin1String GET_FOLLOWED_USERS(R"(select following FROM follow JOIN users u ON u.id = following WHERE follower = ? AND following_state != FALSE)");
// clang-format on

UserModel::UserModel(int id) : id(id) {
  QSqlQuery query;
  // handle client errors
  if (!query.prepare(LOAD_USER_SQL))
    throw query.lastError();
  query.addBindValue(id);
  if (query.exec()) {
    if (query.next()) {
      m_username = query.value(0).toString();
      m_firstname = query.value(1).toString();
      m_lastname = query.value(2).toString();
      m_employment_type = query.value(3).toString();
      m_is_company = query.value(4).toBool();
    } else {
      throw UserNotFoundException();
    }
  } else
    throw query.lastError();
}

UserModel::UserModel(const UserModel &other)
    : id(other.id), m_firstname(other.m_firstname),
      m_username(other.m_username), m_lastname(other.m_lastname),
      m_employment_type(other.m_employment_type),
      m_is_company(other.m_is_company) {}

UserModel UserModel::operator=(const UserModel &other) {
  UserModel model(other);
  return other;
}

int UserModel::getId() const { return id; }

const QString &UserModel::getUsername() const { return m_username; }

const QString &UserModel::getFirstName() const { return m_firstname; }

const QString &UserModel::getLastName() const { return m_lastname; }

const QString &UserModel::getEmploymentType() const {
  return m_employment_type;
}

QString UserModel::getJob() const {
  QSqlQuery query;
  if (!query.prepare(GET_USER_JOB))
    throw query.lastError();
  query.addBindValue(id);
  if (query.exec()) {
    query.next();
    return query.value(0).toString();
  }
  throw query.lastError();
}

QPixmap UserModel::getUserProfile() const {
  QSqlQuery query;
  if (!query.prepare(GET_USER_PROFILE_PICTURE))
    throw query.lastError();
  query.addBindValue(id);
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

QString UserModel::getBioGraphy() const {
  QSqlQuery query;
  if (!query.prepare(GET_USER_BIOGRAPHY))
    throw query.lastError();
  query.addBindValue(id);
  if (!query.exec())
    throw query.lastError();
  query.next();
  return query.value(0).toString();
}

void UserModel::setBiography(const QString &bio) {
  QSqlQuery query;
  if (!query.prepare(UPDATE_USER_BIOGRAPHY))
    throw query.lastError();
  query.addBindValue(bio);
  query.addBindValue(id);
  if (!query.exec())
    throw query.lastError();
}

void UserModel::setUserProfile(const QImage &data) {
  QSqlQuery query;
  if (!query.prepare(UPDATE_USER_PROFILE_PICTURE))
    throw query.lastError();
  QByteArray imageData;
  QBuffer buffer(&imageData);
  data.save(&buffer, "PNG");
  query.addBindValue(imageData.toBase64());
  query.addBindValue(id);
  if (!query.exec())
    throw query.lastError();
}

QList<QString> UserModel::getAbilities() const {
  QSqlQuery query;
  if (!query.prepare(GET_USER_ABILITIES))
    throw query.lastError();
  query.addBindValue(id);
  if (query.exec()) {
    query.next();
    QStringList items = query.value(0).toString().split(",");
    if (items.begin()->isEmpty())
      items.erase(items.begin());
    for (QString &item : items) {
      item.removeLast();
      item.removeFirst();
    }
    return items;
  }
  throw query.lastError();
}

void UserModel::setAbilities(const QStringList &newAbilities) {
  QSqlQuery query;
  if (!query.prepare(UPDATE_USER_ABILITIES))
    throw query.lastError();
  query.addBindValue(util::formatArray(newAbilities));
  query.addBindValue(id);
  if (!query.exec()) {
    throw query.lastError();
  }
}

bool UserModel::isHaveProfile() const {
  QSqlQuery query;
  if (!query.prepare(GET_USER_PROFILE_PICTURE_EXISTENCE))
    throw query.lastError();
  query.addBindValue(id);
  if (query.exec()) {
    query.next();
    return query.value(0).toBool();
  } else
    throw query.lastError();
}

void UserModel::deleteProfile() {
  QSqlQuery query;
  if (!query.prepare(DELETE_USER_PROFILE_PICTURE))
    throw query.lastError();
  query.addBindValue(id);
  if (!query.exec())
    throw query.lastError();
}

void UserModel::logout() const {
  saveLoginInfo("", "", "login.dat", generateKey());
}

void UserModel::follow(const UserModel &model) {
  QSqlQuery query;
  if (!query.prepare(FOLLOW_USER))
    throw query.lastError();
  query.bindValue(":follower", id);
  query.bindValue(":following", model.id);
  if (!query.exec())
    throw query.lastError();
  emit followingChanged(FollowingStates::PendingFollowing, model.id);
}

void UserModel::unfollow(const UserModel &model) {
  QSqlQuery query;
  if (!query.prepare(UNFOLLOW_USER))
    throw query.lastError();
  query.bindValue(":follower", id);
  query.bindValue(":following", model.id);
  if (!query.exec())
    throw query.lastError();
  emit followingChanged(FollowingStates::NoFollowed, model.id);
}

QList<QPair<int, bool>> UserModel::getAllPendingInvitations() {
  QSqlQuery query;
  if (!query.prepare(GET_ALL_PENDING_INVITATIONS))
    SQL_THROW;
  query.addBindValue(id);
  if (query.exec()) {
    QList<QPair<int, bool>> allPendingInvitations;
    while (query.next())
      allPendingInvitations.emplace_back(query.value(0).toInt(),
                                         query.value(1).toBool());
    return allPendingInvitations;
  } else
    SQL_THROW;
}

void UserModel::rejectFollow(int user) { changeFollowState(user, false); }

void UserModel::acceptFollow(int user) { changeFollowState(user, true); }

UserModel::FollowingStates
UserModel::getFollowingState(const UserModel &model) {
  CREATE_SQL(IS_FOLLOWING_USER);
  SQL_BIND_PLACED(":follower", id);
  SQL_BIND_PLACED(":following", model.id);
  if (!query.exec())
    SQL_THROW;
  if (query.next()) {
    auto val = query.value(0);
    if (val.isNull())
      return FollowingStates::PendingFollowing;
    return val.toBool() ? FollowingStates::Followed : FollowingStates::Rejected;
  }
  return FollowingStates::NoFollowed;
}

void UserModel::signUpAsCompany() {
  CREATE_SQL(SIGN_UP_AS_COMPANY);
  SQL_BIND(id);
  if (!query.exec())
    SQL_THROW;
  m_is_company = true;
}

bool UserModel::isCompany() const { return m_is_company; }

bool UserModel::operator==(const UserModel &model) const {
  return model.id == id;
}

QList<PostModel> UserModel::getPosts() {
  CREATE_SQL(GET_USER_POSTS);
  SQL_BIND(id);
  if (!query.exec())
    SQL_THROW;
  QList<PostModel> temp;
  while (query.next()) {
    PostModel model(query.value(0).toInt());
    if (!query.value(1).isNull())
      model.reposted_from = query.value(1).toInt();
    temp.append(model);
  }
  return temp;
}

QList<UserModel> UserModel::getRelatedUsers() {
  CREATE_SQL(GET_RELATED_USERS);
  SQL_BIND_PLACED(":id", id);
  if (query.exec()) {
    QList<UserModel> users;
    while (query.next())
      users.emplace_back(query.value(0).toInt());
    return users;
  } else
    SQL_THROW;
}

QList<int> UserModel::getFollowedUsers() {
  CREATE_SQL(GET_FOLLOWED_USERS);
  SQL_BIND(id);
  if (query.exec()) {
    QList<int> users;
    while (query.next())
      users.push_back(query.value(0).toInt());
    return users;
  } else
    SQL_THROW;
}

void UserModel::changeFollowState(int user, bool state) {
  CREATE_SQL(SET_INVITATION_STATUS);
  SQL_BIND_PLACED(":state", state);
  SQL_BIND_PLACED(":follower", user);
  SQL_BIND_PLACED(":following", id);
  if (!query.exec())
    SQL_THROW;
}

UserNotFoundException::~UserNotFoundException() noexcept {}

const char *UserNotFoundException::what() const noexcept {
  return "The User not found";
}
