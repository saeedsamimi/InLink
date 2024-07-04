#ifndef CREATEJOBDIALOG_H
#define CREATEJOBDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <database/models/companymodel.h>

namespace Ui {
class CreateJobDialog;
}

class CreateJobDialog : public QDialog {
  Q_OBJECT

public:
  explicit CreateJobDialog(QWidget *parent = nullptr);
  int execute(CompanyModel *model);
  ~CreateJobDialog();

private:
  Ui::CreateJobDialog *ui;
  QSqlQueryModel queryModel;
};

#endif // CREATEJOBDIALOG_H
