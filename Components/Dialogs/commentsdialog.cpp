#include "commentsdialog.h"
#include "ui_commentsdialog.h"
#include <Components/Delegates/commentwidget.h>

CommentsDialog::CommentsDialog(UserModel *model, const PostModel &post,
                               QWidget *parent)
    : QDialog(parent), ui(new Ui::CommentsDialog), post_model(post),
      user_model(model),
      post_widget(new PostWidget(model, post, nullptr, false)) {
  ui->setupUi(this);
  qDebug() << "Comments dialog is called for the user by ID:" << model->getId()
           << "\tAnd the post by ID:" << post.getPostId();
  ui->username_lbl->setText(model->getUsername());
  ui->icon_lbl->setPixmap(model->getUserProfile());
  ui->verticalLayout->insertWidget(0, post_widget, 1);
  QAction *createCommentAction = ui->create_command_text_box->addAction(
      QIcon(QPixmap(":/send.png")), QLineEdit::TrailingPosition);
  connect(createCommentAction, &QAction::triggered, this,
          &CommentsDialog::handleClickCreateComment);
  for (auto comment : post.getComments())
    addComment(comment);
}

CommentsDialog::~CommentsDialog() {
  delete ui;
  delete post_widget;
}

void CommentsDialog::handleClickCreateComment() {
  QString commentText = ui->create_command_text_box->text();
  if (!commentText.isEmpty()) {
    qDebug() << "clicked with text : " << ui->create_command_text_box->text();
    Comment newComment =
        post_model.addComment(user_model->getId(), commentText);
    addComment(newComment);
  }
}

void CommentsDialog::addComment(Comment &comment) {
  auto item = new QListWidgetItem();
  auto comment_widget = new CommentWidget(comment);
  item->setSizeHint(comment_widget->sizeHint());
  ui->listWidget->addItem(item);
  ui->listWidget->setItemWidget(item, comment_widget);
}

void CommentsDialog::on_create_command_text_box_returnPressed() {
  QAction *action = ui->create_command_text_box->actions().at(0);
  action->trigger();
}
