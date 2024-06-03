#ifndef SELECTABILITIESDIALOG_H
#define SELECTABILITIESDIALOG_H

#include <database/models/usermodel.h>

#include <QAbstractButton>
#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class SelectAbilitiesDialog;
}

class SelectAbilitiesDialog : public QDialog {
  Q_OBJECT

 public:
  explicit SelectAbilitiesDialog(QStringListModel *list_model, UserModel *model,
                                 QWidget *parent = nullptr);
  ~SelectAbilitiesDialog();

 private slots:
  void on_addBtn_clicked();

  void on_selectionBox_currentIndexChanged(int index);

  void on_btnBox_accepted();

  void on_btnBox_clicked(QAbstractButton *button);

  void handleCurrentItemChanged(const QModelIndex &selection,
                                const QModelIndex &before);

  void on_remBtn_clicked();

 private:
  Ui::SelectAbilitiesDialog *ui;
  QSqlQueryModel model;
  UserModel *user_model;
  QStringListModel *list_model;
};

#endif  // SELECTABILITIESDIALOG_H
