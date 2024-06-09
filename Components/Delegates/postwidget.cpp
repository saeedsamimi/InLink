#include "postwidget.h"

#include <utils/Util.h>

#include "ui_postwidget.h"
#include <Components/Dialogs/commentsdialog.h>

PostWidget::PostWidget(UserModel *user, const PostModel &post, QWidget *parent,
                       bool showButtons)
    : QWidget(parent), ui(new Ui::PostWidget), model(post), user(user),
      owner(model.getUser()), isLiked(model.isLiked(user->getId())) {
  ui->setupUi(this);
  if (*user == owner)
    ui->follow_btn->hide();
  if (!showButtons) {
    ui->bottom_widget->hide();
    ui->bottom_h_line->hide();
  }
  if (isLiked)
    ui->like_link_btn->setText("Liked");
  connect(user, &UserModel::followingChanged, this,
          &PostWidget::handleFollowingChanged);
  updateUserFollowingState();
  ui->content_lbl->setText(
      util::buildColoredLabeled("Content", "3434FF", model.getContent()));
  ui->username_lbl->setText(
      util::buildColoredLabeled("Created By", "3434FF",
                                std::move(owner.getUsername()))
          .append('\n')
          .append(util::buildColoredLabeled("Job", "3434FF",
                                            std::move(owner.getJob()))));

  ui->icon_lbl->setPixmap(owner.getUserProfile());
  if (!post.isHavePicture())
    ui->post_pic_lbl->hide();
  else
    ui->post_pic_lbl->setPixmap(post.getPostPixture());
}

PostWidget::~PostWidget() { delete ui; }

void PostWidget::on_follow_btn_clicked() {
  if (!isFollowing)
    user->follow(owner);
  else
    user->unfollow(owner);
  updateUserFollowingState();
}

void PostWidget::handleFollowingChanged(bool newState, int id) {
  if (id == owner.getId()) {
    if (newState)
      ui->follow_btn->setText("Following");
    else
      ui->follow_btn->setText("Follow");
    isFollowing = newState;
  }
}

void PostWidget::updateUserFollowingState() {
  if (user->isFollowing(owner)) {
    ui->follow_btn->setText("Following");
    isFollowing = true;
  } else
    ui->follow_btn->setText("Follow");
}

void PostWidget::on_comment_link_btn_clicked() {
  qDebug() << "the comment link btn click triggered for id: "
           << model.getPostId();
  CommentsDialog dialog(user, model, this);
  dialog.exec();
}

void PostWidget::on_repost_link_btn_clicked() { model.repost(user->getId()); }

void PostWidget::on_like_link_btn_clicked() {
  if (isLiked) {
    model.removeLike(user->getId());
    ui->like_link_btn->setText("Like");
  } else {
    model.addLike(user->getId());
    ui->like_link_btn->setText("Liked");
  }
  isLiked = !isLiked;
}
