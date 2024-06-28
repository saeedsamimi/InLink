#ifndef COMPANY_H
#define COMPANY_H
#include "account.h"
#include "job.h"
#include "person.h"

class Company : public Account {
public:
  /* Constructors */

  inline Company() = default;
  Company(const QString &comapny_name, const QString &account_id,
          const QString &phone_number, const QString &email);

  /* Getters */

  QString getCompnyName() const;
  QList<Person *> &getEmployees();
  QList<Job *> &getJobs();
  QList<Person *> &getFollowers();

  /* Setters */

  void setCompanyName(QString newName);

  /* Methods */

  void createJob(Job *newjob);

private:
  QString company_name;
  QList<Person *> employees;
  QList<Job *> jobs;
  QList<Person *> followers;
};

#endif // COMPANY_H
