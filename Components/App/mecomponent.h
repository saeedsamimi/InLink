#ifndef MECOMPONENT_H
#define MECOMPONENT_H

#include <Components/Dialogs/selectabilitiesdialog.h>
#include <database/models/companymodel.h>
#include <database/models/usermodel.h>

#include <QWidget>

namespace Ui {
class MeComponent;
}

class MeComponent : public QWidget {
  Q_OBJECT

public:
  explicit MeComponent(UserModel *model, bool editable = true,
                       QWidget *parent = nullptr);
  ~MeComponent();

signals:
  void logout();

private slots:
  void on_editPicBtn_clicked();

  void on_delPicBtn_clicked();

  void on_editBiographyBtn_clicked();

  void on_editAbilityBtn_clicked();

  void handleRejectAbilitiesDialog();

  void on_log_out_btn_clicked();

  void on_theme_btn_clicked();

  void on_sign_as_company_btn_clicked();

private:
  Ui::MeComponent *ui;
  UserModel *model = nullptr;
  SelectAbilitiesDialog *dial = nullptr;
  QStringListModel list_model;

  void resetProfilePictureText();
  void changeToCompanyMode(CompanyModel company_model);

  const static QString label;
};

#endif // MECOMPONENT_H
