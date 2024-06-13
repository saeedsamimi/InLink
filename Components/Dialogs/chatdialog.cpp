#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>

ChatDialog::ChatDialog(UserModel *model, QWidget *parent)
    : QDialog(parent), ui(new Ui::ChatDialog), model(model),
      socket(new QWebSocket) {
  ui->setupUi(this);

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
  delete model;
  delete socket;
}

void ChatDialog::setGlobalUser(UserModel *model) { globalUser = model; }

void ChatDialog::addMessage(int sender, QString content, QDateTime time) {
  auto item = new QListWidgetItem();
  auto widget = new MessageDelegate(sender, content, time);
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
      addMessage(msg["receiver"].toInt(), msg["msg"].toString(),
                 msg["time"].toVariant().toDateTime());
    }
  } else if (obj["type"].toString() == "registerMsg") {
    QJsonValue v = obj["data"];
    addMessage(v["to_id"].toInt(), v["msg"].toString(),
               QDateTime::currentDateTime());
  }
}

void ChatDialog::handleClickSendAction(bool) { qDebug() << "Triggered!"; }

UserModel *ChatDialog::globalUser(nullptr);

void ChatDialog::on_sendBtn_clicked() {
  QJsonObject obj;
  obj["content"] = ui->chat_box->toPlainText();
  QJsonDocument doc(obj);
  socket->sendTextMessage(
      QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}
