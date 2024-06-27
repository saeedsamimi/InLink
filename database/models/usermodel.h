#ifndef USERMODEL_H
#define USERMODEL_H

#include <database/models/postmodel.h>
#include <database/user.h>

#include <QDate>
#include <QObject>
#include <QString>
#include <exception>

class UserNotFoundException : public std::exception {
public:
  ~UserNotFoundException() noexcept override;
  const char *what() const noexcept override;
};

class UserModel : public QObject {
  Q_OBJECT
private:
  const int id;
  QString m_username;
  QString m_firstname;
  QString m_lastname;
  QString m_employment_type;
  bool m_is_company;

public:
  /* Utility enumerators */

  enum FollowingStates { Followed, NoFollowed, PendingFollowing, Rejected };

  /* Constructors */

  UserModel(int id);
  UserModel(const UserModel &other);
  UserModel operator=(const UserModel &other);

  /* Identity getters */

  int getId() const;
  const QString &getUsername() const;
  const QString &getFirstName() const;
  const QString &getLastName() const;
  const QString &getEmploymentType() const;

  /* account and jobs getters */

  QString getJob() const;
  QPixmap getUserProfile() const;
  QString getBioGraphy() const;
  QList<QString> getAbilities() const;
  bool isHaveProfile() const;

  /* account informations setters */

  void setBiography(const QString &bio);
  void setUserProfile(const QImage &data);
  void setAbilities(const QStringList &newAbilities);

  /* account functions methods */

  void deleteProfile();
  void logout() const;

  /* follow and unfollow mechanisem */

  void follow(const UserModel &model);
  void unfollow(const UserModel &model);
  QList<QPair<int, bool>> getAllPendingInvitations();
  void rejectFollow(int user);
  void acceptFollow(int user);
  FollowingStates getFollowingState(const UserModel &model);

  /* company manipulations */

  void signUpAsCompany();
  bool isCompany() const;

  /* usermodel equality check */

  bool operator==(const UserModel &model) const;

  /* Get user's posts */

  [[nodiscard]] QList<PostModel> getPosts();

  /* Get related users */
  [[nodiscard]] QList<UserModel> getRelatedUsers();

signals:
  void followingChanged(FollowingStates newState, int id);
  void onSignedUpAsCompany();

private:
  void changeFollowState(int user, bool state);
};

#endif // USERMODEL_H
