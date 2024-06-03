#ifndef MECOMPONENT_H
#define MECOMPONENT_H

#include <Components/Dialogs/selectabilitiesdialog.h>
#include <database/models/usermodel.h>

#include <QWidget>

namespace Ui {
class MeComponent;
}

class MeComponent : public QWidget {
  Q_OBJECT

 public:
  explicit MeComponent(UserModel *model, QWidget *parent = nullptr);
  ~MeComponent();

 private slots:
  void on_editPicBtn_clicked();

  void on_delPicBtn_clicked();

  void on_editBiographyBtn_clicked();

  void on_editAbilityBtn_clicked();

  void handleRejectAbilitiesDialog();

 private:
  Ui::MeComponent *ui;
  UserModel *model = nullptr;
  SelectAbilitiesDialog *dial = nullptr;
  QStringListModel list_model;

  void resetProfilePictureText();

  const static QString label;
};

#endif  // MECOMPONENT_H
