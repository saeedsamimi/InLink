#include "mecomponent.h"

#include <QFileDialog>
#include <QMessageBox>

#include "ui_mecomponent.h"

MeComponent::MeComponent(const UserModel& model, QWidget* parent)
    : QWidget(parent), ui(new Ui::MeComponent), id(model.getId()) {
  ui->setupUi(this);
  ui->firstName_lbl->setText(
      QString("First Name: %").arg(model.getFirstName()));
  ui->lastName_lbl->setText(QString("First Name: %").arg(model.getLastName()));
}

MeComponent::~MeComponent() { delete ui; }

void MeComponent::on_editPicBtn_clicked() {
  qDebug() << "edit Icon Btn clicked!";
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));
  QPixmap targetPixmap(filename);
  targetPixmap = targetPixmap.scaled(
      ui->profilePicture->width(), ui->profilePicture->height(),
      Qt::KeepAspectRatio, Qt::SmoothTransformation);
  ui->profilePicture->setPixmap(targetPixmap);
}

void MeComponent::on_delPicBtn_clicked() {
  const int ans = QMessageBox::warning(
      this, "Are you sure?", "Are you sure to clear the profile picture?",
      QMessageBox::Yes, QMessageBox::No);
  if (ans == QMessageBox::Yes) {
    ui->profilePicture->clear();
  }
}
