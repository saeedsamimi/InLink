#ifndef USERMODEL_H
#define USERMODEL_H
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

public:
  /* Constructors */

  UserModel(int id);
  UserModel(const UserModel &other);

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
  bool isFollowing(const UserModel &model);

  /* usermodel equality check */

  bool operator==(const UserModel &model) const;

signals:
  void followingChanged(bool newState, int id);
};

#endif // USERMODEL_H
