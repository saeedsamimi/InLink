#ifndef USERMODEL_H
#define USERMODEL_H
#include <database/user.h>

#include <QDate>
#include <QString>
#include <exception>

class UserNotFoundException : public std::exception {
 public:
  ~UserNotFoundException() _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
  const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class UserModel {
 private:
  const int id;
  QString m_username;
  QString m_firstname;
  QString m_lastname;
  QString m_employment_type;

 public:
  UserModel(int id);
  int getId() const;
  const QString& getUsername() const;
  const QString& getFirstName() const;
  const QString& getLastName() const;
  const QString& getEmploymentType() const;
  QPixmap getUserProfile() const;
  QString getBioGraphy() const;
  void setBiography(const QString& bio);
  void setUserProfile(const QImage& data);
  QList<QString> getAbilities() const;
  void setAbilities(const QList<QString>& newAbilities);
  bool isHaveProfile() const;
  void deleteProfile();
};

#endif  // USERMODEL_H
