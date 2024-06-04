#include "homecomponent.h"

#include <Components/Delegates/postwidget.h>
#include <Components/Dialogs/createpostdialog.h>

#include "ui_homecomponent.h"

HomeComponent::HomeComponent(UserModel *model, QWidget *parent)
    : QWidget(parent), ui(new Ui::HomeComponent), model(model),
      posts(std::move(PostModel::getAllPosts())) {
  ui->setupUi(this);
  startPost_action = ui->StartPost_textBox->addAction(
      QIcon(QPixmap(":/arrow-right.png")), QLineEdit::TrailingPosition);
  connect(startPost_action, &QAction::triggered, this,
          &HomeComponent::handleActionCreatePost);
  for (auto item : posts)
    addPost(item);
}

HomeComponent::~HomeComponent() { delete ui; }

void HomeComponent::handleActionCreatePost() {
  qDebug() << "create post triggered!";
  CreatePostDialog *dialog = new CreatePostDialog(model);
  connect(dialog, &CreatePostDialog::postCreated, this,
          &HomeComponent::handlePostCreation);
  dialog->exec();
  delete dialog;
}

void HomeComponent::handlePostCreation(PostModel model) { addPost(model); }

void HomeComponent::addPost(PostModel &model) {
  auto widget_item = new QListWidgetItem();
  auto custom_widget = new PostWidget(model);
  widget_item->setSizeHint(custom_widget->sizeHint());
  ui->Feed->addItem(widget_item);
  ui->Feed->setItemWidget(widget_item, custom_widget);
}
