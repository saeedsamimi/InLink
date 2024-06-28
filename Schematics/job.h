#ifndef JOB_SCHEMA_H
#define JOB_SCHEMA_H
#include <QString>
#include <QStringList>

class Job {
public:
  enum PlaceJob { onSite, Hybrid, Remote };
  inline Job() = default;
  Job(int salary, QString name, QString company_name, PlaceJob type,
      QString location);

  /* Getters */

  int getSalary() const;
  QString getJobName() const;
  QString getComapnyName() const;
  QStringList getRequiredSkilles() const;
  PlaceJob getWorkPlaceType() const;
  QString getLocation() const;

  /* Setters */

  void setSalary(int newsalary);
  void setJobName(QString newName);
  void setComapnyName(QString newName);
  void setWorkplaceType(PlaceJob newType);
  void setLocation(QString newLocation);
  void addAddSkill(QString newSkill);

private:
  int salary;
  QString job_name;
  QString company_name;
  QStringList requiredSkills;
  PlaceJob workPlaceType;
  QString location;
};

#endif // JOB_SCHEMA_H
