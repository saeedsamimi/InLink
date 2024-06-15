#include "mecomponent.h"

#include <Components/Dialogs/companysignin.h>
#include <utils/Util.h>

#include <QApplication>
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

void MeComponent::on_theme_btn_clicked() {
  if (util::getTheme() == util::Dark) {
    util::changeStyle(qobject_cast<QApplication *>(QApplication::instance()),
                      util::Light);
    ui->theme_btn->setIcon(QIcon(":/moon.png"));
  } else {
    util::changeStyle(qobject_cast<QApplication *>(QApplication::instance()),
                      util::Dark);
    ui->theme_btn->setIcon(QIcon(":/sun.png"));
  }
}

void MeComponent::on_sign_as_company_btn_clicked() {
  this->window()->hide();
  /* show the create company dialog */
  CompanySignIn dialog(this);
  connect(&dialog, &CompanySignIn::onSigned, this, []() {
    qDebug() << "unhandled signed event in mecomponent.cpp: line125";
  });
  connect(&dialog, &CompanySignIn::onCanceled, this, []() {
    qDebug() << "unhandled canceled event in mecomponent.cpp: line 127";
  });
  dialog.exec();
  /* hide the create company dialog */
  this->window()->show();
}
