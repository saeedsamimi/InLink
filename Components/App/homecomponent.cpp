#include "homecomponent.h"

#include <Components/Delegates/postwidget.h>
#include <Components/Dialogs/createpostdialog.h>

#include "ui_homecomponent.h"

HomeComponent::HomeComponent(UserModel *model, QWidget *parent)
    : QWidget(parent), ui(new Ui::HomeComponent), model(model),
      posts(std::move(PostModel::getFollowedPosts(model->getId()))) {
  ui->setupUi(this);
  if (posts.length() < 10)
    posts.append(std::move(PostModel::getRelativePosts(model->getId())));
  if (posts.length() < 10)
    posts.append(std::move(PostModel::getLastTenPosts(10 - posts.length())));
  for (auto item : posts)
    addPost(item);
  btn = new QListWidgetItem;
  load_more_btn = new QPushButton("Load more...");
  btn->setSizeHint(load_more_btn->sizeHint());
  ui->Feed->addItem(btn);
  ui->Feed->setItemWidget(btn, load_more_btn);
  connect(ui->start_post_btn, &QAbstractButton::clicked, this,
          &HomeComponent::handleActionCreatePost);
  connect(load_more_btn, &QPushButton::clicked, this,
          &HomeComponent::handleLoadMorePost);
}

HomeComponent::~HomeComponent() {
  delete ui;
  delete load_more_btn;
  delete btn;
}

void HomeComponent::handleActionCreatePost() {
  qDebug() << "create post triggered!";
  CreatePostDialog *dialog = new CreatePostDialog(model);
  connect(dialog, &CreatePostDialog::postCreated, this,
          &HomeComponent::handlePostCreation);
  dialog->exec();
  delete dialog;
}

void HomeComponent::handlePostCreation(PostModel model) {
  posts.insert(0, model);
  addPost(model, true);
}

void HomeComponent::handleLoadMorePost() {
  auto new_posts = PostModel::getLastTenPosts();
  int count = ui->Feed->count() - 1;
  for (auto item : new_posts) {
    addPost(item, count++);
    posts.append(new_posts);
  }
}

void HomeComponent::addPost(PostModel &post_model, int index) {
  try {
    auto widget_item = new QListWidgetItem();
    auto custom_widget = new PostWidget(model, post_model);
    widget_item->setSizeHint(custom_widget->sizeHint());
    if (index >= 0)
      ui->Feed->insertItem(index, widget_item);
    else
      ui->Feed->addItem(widget_item);
    ui->Feed->setItemWidget(widget_item, custom_widget);
    connect(custom_widget, &PostWidget::reposted, this,
            &HomeComponent::handlePostCreation);
  } catch (QSqlError &err) {
    qDebug() << err;
  }
}
