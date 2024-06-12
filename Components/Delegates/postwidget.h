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
                      QWidget *parent = nullptr, bool showButton = true);
  ~PostWidget();

signals:
  void reposted(PostModel post);

private slots:
  void on_follow_btn_clicked();
  void handleFollowingChanged(bool newState, int id);

  void on_comment_link_btn_clicked();

  void on_repost_link_btn_clicked();

  void on_like_link_btn_clicked();

private:
  Ui::PostWidget *ui;
  PostModel model;
  UserModel owner;
  UserModel *user;
  bool isLiked;
  bool isFollowing = false;

  void updateUserFollowingState();
};

#endif // POSTWIDGET_H
