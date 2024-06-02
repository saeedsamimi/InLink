#ifndef MECOMPONENT_H
#define MECOMPONENT_H

#include <database/models/usermodel.h>

#include <QWidget>

namespace Ui {
class MeComponent;
}

class MeComponent : public QWidget {
  Q_OBJECT

 public:
  explicit MeComponent(const UserModel &model, QWidget *parent = nullptr);
  ~MeComponent();

 private slots:
  void on_editPicBtn_clicked();

  void on_delPicBtn_clicked();

 private:
  Ui::MeComponent *ui;
  int id;
};

#endif  // MECOMPONENT_H
