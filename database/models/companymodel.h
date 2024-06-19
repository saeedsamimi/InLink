#ifndef COMPANYMODEL_H
#define COMPANYMODEL_H

#include <QObject>
#include <database/models/usermodel.h>
#include <utils/Util.h>

class CompanyModel : public QObject {
  Q_OBJECT
private:
  explicit CompanyModel(QObject *parent = nullptr);

public:
  CompanyModel(const CompanyModel &);
  static CompanyModel FromUser(UserModel *model);
  static CompanyModel SignUpByUser(UserModel *model, QString name);
  int getId() const;
  QString getName() const;

private:
  int ownerId;
  QString name;
};

#endif // COMPANYMODEL_H
