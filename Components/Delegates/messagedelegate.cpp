#include "messagedelegate.h"
#include "ui_messagedelegate.h"
#include <database/models/usermodel.h>

MessageDelegate::MessageDelegate(int sender_id, QString content, QDateTime time,
                                 QWidget *parent)
    : QFrame(parent), ui(new Ui::MessageDelegate) {
  ui->setupUi(this);
  UserModel sender(sender_id);
  ui->time_lbl->setText(time.toString("yy/MM/dd - hh:mm:ss"));
  ui->content_lbl->setText(content);
  ui->name_lbl->setText(sender.getFirstName() + " " + sender.getLastName());
  ui->icon_lbl->setPixmap(sender.getUserProfile().scaled(
      ui->icon_lbl->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

MessageDelegate::~MessageDelegate() { delete ui; }
