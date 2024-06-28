#ifndef PERSON_H
#define PERSON_H
#include "account.h"
#include "job.h"
#include <QStringList>

class Person : public Account {
public:
  /* Construcrtors */

  inline Person() = default;
  Person(const QString &account_id, const QString &phone_number,
         const QString &email, const QString &firstname,
         const QString &lastname, const QStringList skills);

  /* Getters */

  QString getLastName() const;
  QString getFirstName() const;
  QStringList getSkills() const;

  /* Setters */

  void setLastName(QString newName);
  void setFirstName(QString newName);
  void addSkills(QString skills);
  void removeSkillAt(size_t index);
  void removeSkill(QString skill);
  void resetSkills();

  /* Methods */

  void takeJob(Job &job);

private:
  QString Firstname;
  QString Lastname;
  QStringList skills;
};

#endif // PERSON_H
