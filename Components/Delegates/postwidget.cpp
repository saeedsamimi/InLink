#include "postwidget.h"

#include <QMessageBox>
#include <utils/Util.h>

#include "ui_postwidget.h"
#include <Components/Dialogs/commentsdialog.h>
#include <Components/Dialogs/showprofiledialog.h>

PostWidget::PostWidget(UserModel *user, const PostModel &post, QWidget *parent,
                       bool showButtons)
    : QWidget(parent), ui(new Ui::PostWidget), model(post), user(user),
      owner(model.getUser()), isLiked(model.isLiked(user->getId())) {
  /* setup UI */

  ui->setupUi(this);

  /* ui specialization for specific post states*/

  // usercannot follow himself
  if (user->operator==(owner)) {
    ui->follow_btn->hide();
  }
  // show only post content, not post actions!
  if (!showButtons) {
    ui->bottom_widget->hide();
    ui->profile_btn->hide();
    ui->bottom_h_line->hide();
  }
  // the post when is liked , should be states liked
  if (isLiked) {
    ui->like_link_btn->setText("Liked");
    ui->like_link_btn->setIcon(QIcon(":/like-filled.png"));
  } else {
    ui->like_link_btn->setText("Like");
    ui->like_link_btn->setIcon(QIcon(":/like.png"));
  }
  // updating the user following state
  followState = user->getFollowingState(owner);
  updateUserFollowingStateUtil(followState);
  // set the content data
  ui->content_lbl->setText(
      util::buildColoredLabeled("Content", "3434FF", model.getContent()));

  /* require the label's placeholders */

  QString username_lbl("Created By");
  QString posted_at_lbl("Posted At");
  if (model.isReposted()) {
    username_lbl = "Reposted By";
    posted_at_lbl = "Reposted At";
  }
  // set the labels and datas
  ui->username_lbl->setText(
      util::buildColoredLabeled(username_lbl, "3434FF",
                                std::move(owner.getUsername()))
          .append('\n')
          .append(util::buildColoredLabeled("Job", "3434FF",
                                            std::move(owner.getJob()))));
  ui->posted_at_lbl->setText(util::buildColoredLabeled(
      posted_at_lbl, "3030F0",
      std::move(model.getPostedAtTime().toString("yyyy/MM/dd - HH:mm:SS"))));
  ui->icon_lbl->setPixmap(owner.getUserProfile());
  // hide the picture lbl is needed
  if (!post.isHavePicture())
    ui->post_pic_lbl->hide();
  else
    ui->post_pic_lbl->setPixmap(post.getPostPixture());

  // hide the suggested tag for not suggested users
  if (!post.isSuggested())
    ui->suggest_lbl->hide();
  // connect following changed signal to handleFollowingChanged slot
  connect(user, &UserModel::followingChanged, this,
          &PostWidget::handleFollowingChanged);
}

PostWidget::~PostWidget() { delete ui; }

void PostWidget::on_follow_btn_clicked() {
  if (followState == UserModel::FollowingStates::NoFollowed)
    user->follow(owner);
  else if (followState == UserModel::FollowingStates::Followed)
    user->unfollow(owner);
  else
    return;
  updateUserFollowingState();
}

void PostWidget::handleFollowingChanged(UserModel::FollowingStates newState,
                                        int id) {
  if (id == owner.getId()) {
    updateUserFollowingStateUtil(newState);
    followState = newState;
  }
}

void PostWidget::updateUserFollowingState() {
  updateUserFollowingStateUtil(user->getFollowingState(owner));
}

void PostWidget::updateUserFollowingStateUtil(
    UserModel::FollowingStates state) {
  switch (state) {
  case UserModel::FollowingStates::NoFollowed:
    ui->follow_btn->setText(util::labels[user->isCompany()][0]);
    ui->follow_btn->setIcon(QIcon(":/plus.svg"));
    break;
  case UserModel::FollowingStates::Followed:
    ui->follow_btn->setText(util::labels[user->isCompany()][1]);
    ui->follow_btn->setIcon(QIcon(":/minus.png"));
    break;
  case UserModel::FollowingStates::PendingFollowing:
    ui->follow_btn->setText("Pending");
    ui->follow_btn->setEnabled(false);
    break;
  case UserModel::FollowingStates::Rejected:
    ui->follow_btn->setText("Rejected");
    ui->follow_btn->setEnabled(false);
    break;
  default:
    break;
  }
}

void PostWidget::on_comment_link_btn_clicked() {
  qDebug() << "the comment link btn click triggered for id: "
           << model.getPostId();
  CommentsDialog dialog(user, model, this);
  dialog.exec();
}

void PostWidget::on_repost_link_btn_clicked() {
  try {
    PostModel reposted_post = model.repost(user->getId());
    emit reposted(reposted_post);
  } catch (QSqlError &err) {
    if (err.nativeErrorCode() == "23505")
      QMessageBox::critical(this, "Error",
                            "You have already posted this post!");
    else
      qDebug() << "Error occured while reposting: " << err;
  }
}

void PostWidget::on_like_link_btn_clicked() {
  if (isLiked) {
    model.removeLike(user->getId());
    ui->like_link_btn->setText("Like");
    ui->like_link_btn->setIcon(QIcon(":/like.png"));
  } else {
    model.addLike(user->getId());
    ui->like_link_btn->setText("Liked");
    ui->like_link_btn->setIcon(QIcon(":/like-filled.png"));
  }
  isLiked = !isLiked;
}

void PostWidget::on_profile_btn_clicked() {
  ShowProfileDialog *profile = new ShowProfileDialog(&owner, this);
  profile->exec();
}
