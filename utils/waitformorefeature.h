#ifndef WAITFORMOREFEATURE_H
#define WAITFORMOREFEATURE_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class WaitForMoreFeature;
}

class WaitForMoreFeature : public QDialog {
  Q_OBJECT

 public:
  explicit WaitForMoreFeature(int, QWidget *parent = nullptr);
  ~WaitForMoreFeature();

 private slots:
  void on_buttonBox_rejected();

 private:
  Ui::WaitForMoreFeature *ui;
  int ID;
  QSqlQuery query;
};

#endif  // WAITFORMOREFEATURE_H
