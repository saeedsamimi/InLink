#include "mecomponent.h"

#include <Components/Dialogs/selectabilitiesdialog.h>

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <splashscreen.h>

#include "ui_mecomponent.h"

const QString
    MeComponent::label(R"(<p><span style=" color:#00557f;">%1:</span> %2</p>)");

MeComponent::MeComponent(UserModel *model, bool editable, QWidget *parent)
    : QWidget(parent), ui(new Ui::MeComponent), model(model),
      list_model(model->getAbilities(), this) {
  ui->setupUi(this);
  ui->firstName_lbl->setText(label.arg("First Name", model->getFirstName()));
  ui->lastName_lbl->setText(label.arg("Last Name", model->getLastName()));
  ui->Bio_lbl->setText(label.arg("Biography", model->getBioGraphy()));
  if (model->isHaveProfile()) {
    ui->profilePicture->setPixmap(model->getUserProfile());
  } else {
    qDebug() << "Do not have any profile!";
    resetProfilePictureText();
  }
  ui->listView->setModel(&list_model);
  if (!editable) {
    /* hide something */
    ui->editAbilityBtn->hide();
    ui->editBiographyBtn->hide();
    ui->editPicBtn->hide();
    ui->delPicBtn->hide();
    ui->sign_as_company_btn->hide();
    ui->log_out_btn->hide();
  }
}

MeComponent::~MeComponent() {
  delete ui;
  delete dial;
}

void MeComponent::on_editPicBtn_clicked() {
  qDebug() << "edit Icon Btn clicked!";
  QString filename = QFileDialog::getOpenFileName(this, "Open Image", "/",
                                                  "Image Files (*.png)");
  QPixmap targetPixmap(filename);
  if (!targetPixmap.isNull()) {
    targetPixmap = targetPixmap.scaled(
        ui->profilePicture->width(), ui->profilePicture->height(),
        Qt::KeepAspectRatio, Qt::SmoothTransformation);
    model->setUserProfile(targetPixmap.toImage());
    ui->profilePicture->setPixmap(targetPixmap);
    ui->delPicBtn->setEnabled(true);
  }
}

void MeComponent::on_delPicBtn_clicked() {
  const int ans = QMessageBox::warning(
      this, "Are you sure?", "Are you sure to clear the profile picture?",
      QMessageBox::Yes, QMessageBox::No);
  if (ans == QMessageBox::Yes) {
    model->deleteProfile();
    resetProfilePictureText();
  }
}

void MeComponent::resetProfilePictureText() {
  ui->delPicBtn->setEnabled(false);
  ui->profilePicture->clear();
  ui->profilePicture->setText("You don't have profile!");
}

void MeComponent::on_editBiographyBtn_clicked() {
  bool ok;
  QString text = QInputDialog::getMultiLineText(
      this, "Edit biography", "Write a summary about yourself",
      model->getBioGraphy(), &ok);
  if (ok) {
    if (text.isEmpty())
      text = "Unknown";
    model->setBiography(text);
    ui->Bio_lbl->setText(label.arg("Biography", text));
  }
}

void MeComponent::on_editAbilityBtn_clicked() {
  dial = new SelectAbilitiesDialog(&list_model, model, this);
  connect(dial, &QDialog::rejected, this,
          &MeComponent::handleRejectAbilitiesDialog);
  dial->exec();
}

void MeComponent::handleRejectAbilitiesDialog() {
  qDebug() << "Handle Rejected Abilities Dialog is triggered!";
  list_model.setStringList(model->getAbilities());
}

void MeComponent::on_log_out_btn_clicked() {
  model->logout();
  emit logout();
}
