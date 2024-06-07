#ifndef USERMODEL_H
#define USERMODEL_H
#include <database/user.h>

#include <QDate>
#include <QObject>
#include <QString>
#include <exception>

class UserNotFoundException : public std::exception {
public:
  ~UserNotFoundException() _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
  const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class UserModel : public QObject {
  Q_OBJECT
private:
  const int id;
  QString m_username;
  QString m_firstname;
  QString m_lastname;
  QString m_employment_type;

public:
  UserModel(int id);
  UserModel(const UserModel &other);
  int getId() const;
  const QString &getUsername() const;
  const QString &getFirstName() const;
  const QString &getLastName() const;
  const QString &getEmploymentType() const;
  QString getJob() const;
  QPixmap getUserProfile() const;
  QString getBioGraphy() const;
  void setBiography(const QString &bio);
  void setUserProfile(const QImage &data);
  QList<QString> getAbilities() const;
  void setAbilities(const QList<QString> &newAbilities);
  bool isHaveProfile() const;
  void deleteProfile();
  void logout() const;
  void follow(const UserModel &model);
  void unfollow(const UserModel &model);
  bool isFollowing(const UserModel &model);
  bool operator==(const UserModel &model) const;

signals:
  void followingChanged(bool newState, int id);
};

#endif // USERMODEL_H
