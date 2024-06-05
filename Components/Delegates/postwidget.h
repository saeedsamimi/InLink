#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <database/models/postmodel.h>

#include <QWidget>

namespace Ui {
class PostWidget;
}

class PostWidget : public QWidget {
  Q_OBJECT

public:
  explicit PostWidget(UserModel *user, const PostModel &text,
                      QWidget *parent = nullptr);
  ~PostWidget();

private slots:
  void on_follow_btn_clicked();

private:
  Ui::PostWidget *ui;
  PostModel model;
  UserModel owner;
  UserModel *user;
  bool isFollowing = false;

  void updateUserFollowingState();
};

#endif // POSTWIDGET_H
