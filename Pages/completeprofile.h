#ifndef COMPLETEPROFILE_H
#define COMPLETEPROFILE_H

#include <utils/preventclosingeventfilter.h>

#include <QCompleter>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QWidget>

namespace Ui {
class CompleteProfile;
}

class CompleteProfile : public QWidget {
  Q_OBJECT

 public:
  explicit CompleteProfile(int ID, QWidget *parent = nullptr);
  ~CompleteProfile();

 protected:
  void closeEvent(QCloseEvent *event);

 private slots:
  void onCloseRequested();

  void on_continueBtn_clicked();

  void on_firstNameInput_editingFinished();

  void on_lastNameInput_editingFinished();

  void on_dateEdit_editingFinished();

  void on_notStudentCheckBox_clicked(bool checked);

  void on_countryCombobox_activated(int index);

  void on_cityCombobox_activated(int index);

  void on_schoolCombobox_activated(int index);

  void on_startYearSpinbox_editingFinished();

  void on_endYearSpibbox_editingFinished();

  void on_mostRecentJobInput_activated(int index);

  void on_empTypeCombobox_activated(int index);

  void on_mostRecentCompanyInput_editingFinished();

 private:
  Ui::CompleteProfile *ui;
  PreventClosingEventFilter closeFilter;
  QSqlQueryModel jobModel;
  QSqlQueryModel countryModel;
  QSqlQueryModel cityModel;
  QSqlQueryModel universityModel;
  QSqlQueryModel companyModel;
  QCompleter companyCompleter;
  int ID;

  void changeCityModel(int countryIndex);
};

#endif  // COMPLETEPROFILE_H
