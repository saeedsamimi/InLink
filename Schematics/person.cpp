#include "person.h"

Person::Person(const QString &account_id, const QString &phone_number,
               const QString &email, const QString &firstname,
               const QString &lastname, const QStringList skills)
    : Account(account_id, phone_number, email), Firstname(firstname),
      Lastname(lastname), skills(skills) {}

QString Person::getLastName() const { return Lastname; }

QString Person::getFirstName() const { return Firstname; }

QStringList Person::getSkills() const { return skills; }

void Person::setLastName(QString newname) { Firstname = newname; }

void Person::setFirstName(QString newname) { Lastname = newname; }

void Person::addSkills(QString skills) { skills.append(skills); }

void Person::removeSkillAt(size_t index) { skills.removeAt(index); }

void Person::removeSkill(QString skill) {
  skills.removeIf([skill](const QString &sk) { return sk == skill; });
}

void Person::resetSkills() { skills.clear(); }

void Person::takeJob(Job &job) {
  job.getComapnyName().append(job.getJobName());
}
