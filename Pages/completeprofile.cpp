#include "completeprofile.h"

#include <Pages/mainwindow.h>
#include <QMessageBox>
#include <QSqlQuery>
#include <database/user.h>
#include <utils/Util.h>

#include "ui_completeprofile.h"

CompleteProfile::CompleteProfile(int ID, QWidget *parent)
    : QWidget(parent), ID(ID), closeFilter(parent), jobModel(this),
      countryModel(this), cityModel(this), universityModel(this),
      companyModel(this), companyCompleter(this), ui(new Ui::CompleteProfile) {
  installEventFilter(&closeFilter);
  jobModel.setQuery("SELECT job_name FROM jobs;");
  countryModel.setQuery("SELECT name FROM countries order by id;");
  changeCityModel(0);
  ui->setupUi(this);
  // enable styles and add connections
  ui->mostRecentJobInput->setModel(&jobModel);
  ui->countryCombobox->setModel(&countryModel);
  ui->cityCombobox->setModel(&cityModel);
  ui->schoolCombobox->setModel(&universityModel);
  ui->empTypeCombobox->addItems(QStringList{"Apprenticeship", "Traineeship",
                                            "Contract employment", "Casual",
                                            "Seasonal employees"});
  companyCompleter.setModel(&companyModel);
  companyCompleter.setFilterMode(Qt::MatchContains);
  companyCompleter.setCaseSensitivity(Qt::CaseInsensitive);
  ui->mostRecentCompanyInput->setCompleter(&companyCompleter);
  enableStyle(ui->continueBtn, "PBS.qss");
  enableStyle(this, "CPS.qss");
  if (!QSqlDatabase::database().transaction())
    qDebug() << QSqlDatabase::database().lastError();
  connect(&closeFilter, &PreventClosingEventFilter::onCloseRequested, this,
          &CompleteProfile::onCloseRequested);
}

CompleteProfile::~CompleteProfile() { delete ui; }

void CompleteProfile::closeEvent(QCloseEvent *event) {
  if (closeFilter.isDisabled()) {
    if (!QSqlDatabase::database().commit())
      QMessageBox::critical(nullptr, "Error",
                            "The information not saved. an error occured");
    else {
      MainWindow *window = new MainWindow(UserModel(ID));
      window->show();
    }
  }
  QWidget::closeEvent(event);
}

void CompleteProfile::onCloseRequested() {
  if (QSqlDatabase::database().rollback())
    qDebug() << "data saved successfully!";
}

void CompleteProfile::on_continueBtn_clicked() {
  if (ui->startYearSpinbox->value() > QDate::currentDate().year()) {
    QMessageBox::critical(this, "Error in year selecting!",
                          "You cannot start from newer years!");
    return;
  }
  if (ui->endYearSpibbox->value() > QDate::currentDate().year()) {
    QMessageBox::critical(this, "Error in year selecting!",
                          "You cannot end in newer years!");
    return;
  }
  if (ui->endYearSpibbox->value() < ui->startYearSpinbox->value()) {
    QMessageBox::critical(this, "Error in year selecting!",
                          "You cannot end past when you start!");
    return;
  }
  if (ui->firstNameInput->text().isEmpty() ||
      ui->lastNameInput->text().isEmpty()) {
    QMessageBox::critical(this, "Error in input name!",
                          "Please specify your first name and last name!");
    return;
  }
  // run all savings
  on_firstNameInput_editingFinished();
  on_lastNameInput_editingFinished();
  on_dateEdit_editingFinished();
  on_notStudentCheckBox_clicked(true);
  on_countryCombobox_activated(-1);
  on_cityCombobox_activated(ui->cityCombobox->currentIndex());
  on_schoolCombobox_activated(ui->schoolCombobox->currentIndex());
  on_empTypeCombobox_activated(ui->empTypeCombobox->currentIndex());
  on_mostRecentCompanyInput_editingFinished();
  on_mostRecentJobInput_activated(ui->mostRecentJobInput->currentIndex());
  on_endYearSpibbox_editingFinished();
  on_startYearSpinbox_editingFinished();
  changeAccountLevel(ID, FullyActivated);
  // end of running all savings
  closeFilter.disable();
  close();
}

void CompleteProfile::on_firstNameInput_editingFinished() {
  if (ui->firstNameInput->text().isEmpty())
    return;
  try {
    updateUserIdentity(this->ID, FirstName, this->ui->firstNameInput->text());
  } catch (QSqlError &e) {
    QMessageBox::critical(this, "Error while saving", e.databaseText());
  }
}

void CompleteProfile::on_lastNameInput_editingFinished() {
  if (ui->lastNameInput->text().isEmpty())
    return;
  try {
    updateUserIdentity(this->ID, LastName, this->ui->lastNameInput->text());
  } catch (QSqlError &e) {
    QMessageBox::critical(this, "Error while saving", e.databaseText());
  }
}

void CompleteProfile::on_dateEdit_editingFinished() {
  QDate date = ui->dateEdit->date();
  if (date > QDate::currentDate()) {
    QMessageBox::critical(this, "Error in using time!",
                          "The selected time is newer than now!");
    return;
  }
  if (date.year() + 5 > QDate::currentDate().year()) {
    QMessageBox::critical(this, "Error in choosing birthDate",
                          "The user must at least five years");
    return;
  }
  updateUserIdentity(ID, BirthDate, date.toString("yyyy/MM/dd"));
}

void CompleteProfile::on_notStudentCheckBox_clicked(bool checked) {
  ui->educationInfoGroupBox->setEnabled(!checked);
  try {
    updateUserIdentity(ID, IsStudent, checked);
  } catch (QSqlError &e) {
    QMessageBox::critical(this, "Error while saving", e.databaseText());
  }
}

void CompleteProfile::on_countryCombobox_activated(int index) {
  if (index == ui->countryCombobox->currentIndex())
    changeCityModel(index);
  updateUserIdentity(ID, Country, ui->countryCombobox->currentText());
}

void CompleteProfile::changeCityModel(int countryIndex) {
  cityModel.setQuery(QString("SELECT city FROM cities WHERE country_id = %1")
                         .arg(countryIndex));
  universityModel.setQuery(
      QString("SELECT university FROM universities WHERE country_id = %1")
          .arg(countryIndex));
  companyModel.setQuery(
      QString("SELECT company FROM companies WHERE country_id = %1")
          .arg(countryIndex));
}

void CompleteProfile::on_cityCombobox_activated(int index) {
  updateUserIdentity(ID, City, ui->cityCombobox->currentText());
}

void CompleteProfile::on_schoolCombobox_activated(int index) {
  updateUserIdentity(ID, School, ui->schoolCombobox->currentText());
}

void CompleteProfile::on_startYearSpinbox_editingFinished() {
  updateUserIdentity(ID, StartYear, ui->startYearSpinbox->value());
}

void CompleteProfile::on_endYearSpibbox_editingFinished() {
  updateUserIdentity(ID, EndYear, ui->endYearSpibbox->value());
}

void CompleteProfile::on_mostRecentJobInput_activated(int index) {
  updateUserIdentity(ID, RecentJob, ui->mostRecentJobInput->currentText());
}

void CompleteProfile::on_empTypeCombobox_activated(int index) {
  updateUserIdentity(ID, EmploymentType, ui->empTypeCombobox->currentText());
}

void CompleteProfile::on_mostRecentCompanyInput_editingFinished() {
  updateUserIdentity(ID, RecentCompany, ui->mostRecentCompanyInput->text());
}
