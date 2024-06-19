#ifndef COMPANYSIGNIN_H
#define COMPANYSIGNIN_H

#include <QDialog>
#include <database/models/companymodel.h>
#include <database/models/usermodel.h>

namespace Ui {
class CompanySignIn;
}

class CompanySignIn : public QDialog {
  Q_OBJECT

public:
  explicit CompanySignIn(UserModel *model, QWidget *parent = nullptr);
  ~CompanySignIn();

signals:
  void onSigned(CompanyModel company);

private slots:
  void on_dialogButtonBox_accepted();

  void on_dialogButtonBox_rejected();

private:
  Ui::CompanySignIn *ui;
  UserModel *model;
};

#endif // COMPANYSIGNIN_H
