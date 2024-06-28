#include "company.h"

Company::Company(const QString &comapny_name, const QString &account_id,
                 const QString &phone_number, const QString &email)
    : company_name(comapny_name), Account(account_id, phone_number, email) {}

QString Company::getCompnyName() const { return company_name; }

QList<Person *> &Company::getEmployees() { return employees; }

QList<Job *> &Company::getJobs() { return jobs; }

QList<Person *> &Company::getFollowers() { return followers; }

void Company::setCompanyName(QString newName) { company_name = newName; }

void Company::createJob(Job *newjob) { jobs.append(newjob); }
