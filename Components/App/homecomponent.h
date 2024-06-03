#ifndef HOMECOMPONENT_H
#define HOMECOMPONENT_H

#include <database/models/postmodel.h>

#include <QSqlQueryModel>
#include <QWidget>

namespace Ui {
class HomeComponent;
}

class HomeComponent : public QWidget {
  Q_OBJECT

 public:
  explicit HomeComponent(QWidget *parent = nullptr);
  ~HomeComponent();

 private slots:

 private:
  Ui::HomeComponent *ui;
  QAction *startPost_action;
  QList<PostModel> posts;
};

#endif  // HOMECOMPONENT_H
