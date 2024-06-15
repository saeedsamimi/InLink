#ifndef COMPANYSIGNIN_H
#define COMPANYSIGNIN_H

#include <QDialog>

namespace Ui {
class CompanySignIn;
}

class CompanySignIn : public QDialog {
  Q_OBJECT

public:
  explicit CompanySignIn(QWidget *parent = nullptr);
  ~CompanySignIn();

signals:
  void onSigned();
  void onCanceled();

private slots:
  void on_dialogButtonBox_accepted();

  void on_dialogButtonBox_rejected();

private:
  Ui::CompanySignIn *ui;
};

#endif // COMPANYSIGNIN_H
