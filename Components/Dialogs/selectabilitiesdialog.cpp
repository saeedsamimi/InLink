#include "selectabilitiesdialog.h"

#include "ui_selectabilitiesdialog.h"

SelectAbilitiesDialog::SelectAbilitiesDialog(QStringListModel* list_model,
                                             UserModel* user_model,
                                             QWidget* parent)
    : QDialog(parent),
      ui(new Ui::SelectAbilitiesDialog),
      model(this),
      user_model(user_model),
      list_model(list_model) {
  ui->setupUi(this);
  model.setQuery("SELECT skill FROM Abilities;");
  ui->selectionBox->setModel(&model);
  ui->listView->setModel(list_model);
  ui->selectionBox->setCurrentIndex(-1);
  connect(ui->listView->selectionModel(), &QItemSelectionModel::currentChanged,
          this, &SelectAbilitiesDialog::handleCurrentItemChanged);
}

SelectAbilitiesDialog::~SelectAbilitiesDialog() { delete ui; }

void SelectAbilitiesDialog::on_addBtn_clicked() {
  if (list_model->insertRow(0)) {
    QModelIndex index = list_model->index(0);
    list_model->setData(index, ui->selectionBox->currentText());
  }
  ui->selectionBox->setCurrentIndex(-1);
}

void SelectAbilitiesDialog::on_selectionBox_currentIndexChanged(int index) {
  if (index != -1) {
    QString currentText = ui->selectionBox->currentText();
    if (list_model->match(list_model->index(0), Qt::DisplayRole, currentText)
            .isEmpty())
      ui->addBtn->setEnabled(true);
    else
      ui->addBtn->setEnabled(false);
  } else
    ui->addBtn->setEnabled(false);
}

void SelectAbilitiesDialog::on_btnBox_accepted() {
  qDebug() << "Accepted(Saving)!";
  user_model->setAbilities(list_model->stringList());
}

void SelectAbilitiesDialog::on_btnBox_clicked(QAbstractButton* button) {
  if (ui->btnBox->buttonRole(button) == QDialogButtonBox::ResetRole)
    list_model->removeRows(0, list_model->rowCount());
}

void SelectAbilitiesDialog::handleCurrentItemChanged(
    const QModelIndex& selection, const QModelIndex& before) {
  ui->remBtn->setEnabled(selection.isValid());
}

void SelectAbilitiesDialog::on_remBtn_clicked() {
  list_model->removeRow(ui->listView->selectionModel()->currentIndex().row());
}
