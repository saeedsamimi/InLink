#include "job.h"

Job::Job(int salary, QString name, QString company_name, PlaceJob type,
         QString location)
    : salary(salary), job_name(name), company_name(company_name),
      workPlaceType(type), location(location) {}

int Job::getSalary() const { return salary; }

QString Job::getJobName() const { return job_name; }

QString Job::getComapnyName() const { return company_name; }

QStringList Job::getRequiredSkilles() const { return requiredSkills; }

Job::PlaceJob Job::getWorkPlaceType() const { return workPlaceType; }

QString Job::getLocation() const { return location; }

void Job::setSalary(int newsalary) { salary = newsalary; }

void Job::setJobName(QString newName) { job_name = newName; }

void Job::setComapnyName(QString newName) { company_name = newName; }

void Job::setWorkplaceType(PlaceJob newType) { workPlaceType = newType; }

void Job::setLocation(QString newLocation) { location = newLocation; }

void Job::addAddSkill(QString newSkill) { requiredSkills.append(newSkill); }
