#ifndef HOMECOMPONENT_H
#define HOMECOMPONENT_H

#include <database/models/postmodel.h>

#include <QSqlQueryModel>
#include <QWidget>
#include <database/models/usermodel.h>

namespace Ui {
class HomeComponent;
}

class HomeComponent : public QWidget {
  Q_OBJECT

public:
  explicit HomeComponent(UserModel *model, QWidget *parent = nullptr);
  ~HomeComponent();

private slots:
  void handleActionCreatePost();
  void handlePostCreation(PostModel model);

private:
  Ui::HomeComponent *ui;
  QAction *startPost_action;
  UserModel *model;
  QList<PostModel> posts;

  void addPost(PostModel &model);
};

#endif // HOMECOMPONENT_H
