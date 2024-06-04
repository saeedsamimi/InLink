#include "postwidget.h"

#include <utils/Util.h>

#include "ui_postwidget.h"

PostWidget::PostWidget(const PostModel &post, QWidget *parent)
    : QWidget(parent), ui(new Ui::PostWidget), model(post),
      owner(model.getUser()) {
  ui->setupUi(this);
  ui->content_lbl->setText(
      util::buildColoredLabeled("Content", "3434FF", model.getContent()));
  ui->username_lbl->setText(
      util::buildColoredLabeled("Created By", "3434FF",
                                std::move(owner.getUsername()))
          .append('\n')
          .append(util::buildColoredLabeled("Job", "3434FF",
                                            std::move(owner.getJob()))));

  ui->icon_lbl->setPixmap(owner.getUserProfile());
  if (!post.isHavePicture()) {
    ui->post_pic_lbl->hide();
  } else {
    ui->post_pic_lbl->setPixmap(post.getPostPixture());
  }
}

PostWidget::~PostWidget() { delete ui; }
