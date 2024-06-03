#include "postwidget.h"

#include "ui_postwidget.h"

PostWidget::PostWidget(const PostModel& post, QWidget* parent)
    : QWidget(parent),
      ui(new Ui::PostWidget),
      model(post),
      owner(model.getUser()) {
  ui->setupUi(this);
  ui->content_lbl->setText(model.getContent());
  ui->username_lbl->setText(owner.getUsername());
  ui->icon_pic->setPixmap(owner.getUserProfile());
  if (!post.isHavePicture()) {
    ui->post_pic->hide();
  } else {
    qDebug() << "unhandled section in line 17 of PostWidget.cpp";
  }
}

PostWidget::~PostWidget() { delete ui; }
