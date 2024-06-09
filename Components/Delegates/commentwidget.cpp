#include "commentwidget.h"
#include "ui_commentwidget.h"
#include <database/models/usermodel.h>
#include <utils/Util.h>

CommentWidget::CommentWidget(Comment comment, QWidget *parent)
    : QWidget(parent), ui(new Ui::CommentWidget), comment(comment) {
  ui->setupUi(this);
  ui->content_lbl->setText(comment.getContent());
  UserModel owner(comment.getUserId());
  ui->username_lbl->setText(
      util::buildColoredLabeled("Username", "3434FF", owner.getUsername()));
  ui->icon_lbl->setPixmap(owner.getUserProfile());
  ui->time_lbl->setText(
      comment.getCommentTime().toString("yyyy/MM/dd - HH:mm"));
}

CommentWidget::~CommentWidget() { delete ui; }
