#include "showprofiledialog.h"
#include <Components/Delegates/postwidget.h>

ShowProfileDialog::ShowProfileDialog(UserModel *model, QWidget *parent)
    : QDialog(parent), ui(new ShowProfileDialogUi), model(model) {
  ui->setupUi(model, this);
  QList<PostModel> posts = model->getPosts();
  for (PostModel &model : posts)
    addPost(model);
  resize(1200, size().height());
}

ShowProfileDialog::~ShowProfileDialog() { delete ui; }

void ShowProfileDialog::addPost(PostModel &post) {
  try {
    auto widget_item = new QListWidgetItem();
    auto item_widget = new PostWidget(model, post, nullptr, false);
    widget_item->setSizeHint(item_widget->sizeHint());
    ui->posts->addItem(widget_item);
    ui->posts->setItemWidget(widget_item, item_widget);
  } catch (QSqlError &err) {
    qDebug() << err;
  }
}

void ShowProfileDialogUi::setupUi(UserModel *model, QDialog *parent) {
  parent->setWindowTitle("Show Profile");
  layout = new QGridLayout(parent);
  profile = new MeComponent(model, false);
  posts = new QListWidget(parent);
  posts_lbl = new QLabel("Posts:");

  QFont posts_lbl_font = posts->font();
  posts_lbl_font.setPointSize(18);
  posts_lbl->setFont(posts_lbl_font);
  posts->setEditTriggers(QListWidget::NoEditTriggers);
  posts->setMinimumSize(QSize(0, 200));
  posts->setVerticalScrollMode(QListWidget::ScrollPerPixel);
  layout->addWidget(profile, 0, 0, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);
  layout->addWidget(posts_lbl, 0, 1, 1, 1, Qt::AlignTop);
  layout->addWidget(posts, 1, 1, 1, 1);
  layout->setRowStretch(0, 1);
  layout->setRowStretch(1, 8);
}

ShowProfileDialogUi::~ShowProfileDialogUi() {
  delete layout;
  delete profile;
  delete posts;
  delete posts_lbl;
}
