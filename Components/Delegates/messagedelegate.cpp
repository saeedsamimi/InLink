#include "messagedelegate.h"
#include "ui_messagedelegate.h"
#include <Components/Dialogs/chatdialog.h>
#include <database/models/usermodel.h>

MessageDelegate::MessageDelegate(int sender_id, QString content,
                                 const QString &pixmap_path, QDateTime time,
                                 QWidget *parent)
    : QFrame(parent), ui(new Ui::MessageDelegate), pic_lbl(nullptr) {
  ui->setupUi(this);
  if (sender_id == ChatDialog::getGlobalUser()->getId())
    setLayoutDirection(Qt::RightToLeft);
  UserModel sender(sender_id);
  ui->time_lbl->setText(time.toString("yy/MM/dd - hh:mm:ss"));
  ui->content_lbl->setText(content);
  ui->name_lbl->setText(sender.getFirstName() + " " + sender.getLastName());
  auto userProfile = sender.getUserProfile();
  if (!userProfile.isNull()) // prevent from scaling null pixmap
    ui->icon_lbl->setPixmap(userProfile.scaled(
        ui->icon_lbl->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
  if (!pixmap_path.isEmpty()) {
    pic_lbl = new QLabel;
    QByteArray imageData = QByteArray::fromBase64(pixmap_path.toLatin1());
    QPixmap pixmap;
    pixmap.loadFromData(imageData);

    pic_lbl->setFixedSize(100, 100);
    pic_lbl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pic_lbl->setPixmap(pixmap);
    ui->msg_box->insertWidget(1, pic_lbl, 0,
                              Qt::AlignVCenter | Qt::AlignHCenter);
  }
}

MessageDelegate::~MessageDelegate() {
  delete ui;
  delete pic_lbl;
}
