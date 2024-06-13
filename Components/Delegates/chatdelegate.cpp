#include "chatdelegate.h"
#include "ui_chatdelegate.h"
#include <utils/Util.h>

ChatDelegate::ChatDelegate(int id, QWidget *parent)
    : QWidget(parent), ui(new Ui::ChatDelegate), model(new UserModel(id)),
      dialog(nullptr) {
  ui->setupUi(this);
  QPixmap picture(model->getUserProfile());
  picture = picture.scaled(ui->icon_lbl->size(), Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);
  ui->username_lbl->setText(model->getFirstName() + ' ' + model->getLastName());
  ui->icon_lbl->setPixmap(picture);
}

ChatDelegate::~ChatDelegate() {
  delete ui;
  delete model;
  delete dialog;
}

void ChatDelegate::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    dialog = new ChatDialog(model, this);
    dialog->exec();
  }
  QWidget::mousePressEvent(event);
}
