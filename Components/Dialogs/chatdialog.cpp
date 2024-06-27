#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>

ChatDialog::ChatDialog(UserModel *model, QWidget *parent)
    : QDialog(parent), ui(new Ui::ChatDialog), model(model),
      socket(new QWebSocket) {
  ui->setupUi(this);

  /* in the first time hide the picture */
  ui->msg_pic_lbl->hide();
  /* initializing the view functionalities */
  QString name = model->getFirstName() + ' ' + model->getLastName();
  setWindowTitle("Chat with: " + name);
  QPixmap prof = model->getUserProfile();
  prof = prof.scaled(ui->icon_lbl->size(), Qt::KeepAspectRatio,
                     Qt::SmoothTransformation);
  ui->icon_lbl->setPixmap(prof);
  ui->username_lbl->setText(name);

  /* initializing the socket */

  connect(socket, &QWebSocket::textMessageReceived, this,
          &ChatDialog::textMessageReceived);

  QUrl url("ws://localhost:3000/message");
  QUrlQuery query(url);
  query.addQueryItem("user_id", QString::number(globalUser->getId()));
  query.addQueryItem("to_id", QString::number(model->getId()));
  url.setQuery(query);
  socket->open(url);
}

ChatDialog::~ChatDialog() {
  delete ui;
  delete socket;
}

void ChatDialog::setGlobalUser(UserModel *model) { globalUser = model; }

UserModel *ChatDialog::getGlobalUser() { return globalUser; }

void ChatDialog::addMessage(int sender, QString content, QDateTime time,
                            const QString &pixmap_path) {
  auto item = new QListWidgetItem();
  auto widget = new MessageDelegate(sender, content, pixmap_path, time);
  item->setSizeHint(widget->sizeHint());
  ui->messages_lbl->addItem(item);
  ui->messages_lbl->setItemWidget(item, widget);
}

void ChatDialog::textMessageReceived(QString message) {
  QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
  QJsonObject obj(doc.object());
  if (obj["type"].toString() == "init") {
    QJsonArray msgs = obj["data"].toArray();
    for (const QJsonValue &value : msgs) {
      QJsonObject msg(value.toObject());
      addMessage(msg["sender"].toInt(), msg["msg"].toString(),
                 msg["time"].toVariant().toDateTime(),
                 msg["picture"].toString());
    }
  } else if (obj["type"].toString() == "registerMsg") {
    QJsonValue v = obj["data"];
    addMessage(v["from_id"].toInt(), v["msg"].toString(),
               QDateTime::currentDateTime(), v["picture"].toString());
  }
  ui->messages_lbl->scrollToBottom();
}

void ChatDialog::handleClickSendAction(bool) { qDebug() << "Triggered!"; }

UserModel *ChatDialog::globalUser(nullptr);

void ChatDialog::on_sendBtn_clicked() {
  QString content = ui->chat_box->toPlainText();
  QPixmap pixmap = ui->msg_pic_lbl->pixmap();
  if (!content.isEmpty()) {
    QJsonObject obj;
    obj["content"] = content;
    if (!pixmap.isNull()) {
      QImage img(pixmap.toImage());
      QByteArray bytes;
      QBuffer buffer(&bytes);
      img.save(&buffer, "PNG");
      obj["picture"] = QString::fromLatin1(bytes.toBase64());
    }
    QJsonDocument doc(obj);
    socket->sendTextMessage(doc.toJson(QJsonDocument::Compact));
    ui->chat_box->clear();
    ui->msg_pic_lbl->hide();
  }
}

void ChatDialog::on_addFileBtn_clicked() {
  QString filePath = QFileDialog::getOpenFileName(this, "Choose a picture", "/",
                                                  "PNG files(*.png)");
  QImage img(filePath);
  if (!img.isNull()) {
    QPixmap pixmap(QPixmap::fromImage(img));
    pixmap = pixmap.scaled(ui->msg_pic_lbl->size(), Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);
    ui->msg_pic_lbl->setPixmap(pixmap);
    ui->msg_pic_lbl->show();
  }
}
