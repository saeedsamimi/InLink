#include "createpostdialog.h"
#include "ui_createpostdialog.h"
#include <QFileDialog>

CreatePostDialog::CreatePostDialog(UserModel *model, QWidget *parent)
    : QDialog(parent), ui(new Ui::CreatePostDialog), model(model) {
  ui->setupUi(this);
}

CreatePostDialog::~CreatePostDialog() { delete ui; }

void CreatePostDialog::on_CreatePostDialog_accepted() {
  qDebug() << "Create Post Dialog Accepted";
  QString text = ui->post_content->toPlainText();
  QImage *image = nullptr;
  if (!img.isNull())
    image = new QImage(img.toImage());
  emit postCreated(PostModel::registerNewPost(model->getId(), &text, image));
  delete image;
}

void CreatePostDialog::on_select_pic_clicked() {
  QString filename = QFileDialog::getOpenFileName(this, "Select Picture", "/",
                                                  "Image Files (*.png)");
  img = QPixmap(filename);
  if (!img.isNull()) {
    img = img.scaled(ui->post_pic->height(), ui->post_pic->width(),
                     Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->post_pic->setPixmap(img);
  } else
    img = QPixmap();
}
