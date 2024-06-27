#include "chatcomponent.h"
#include "ui_chatcomponent.h"
#include <Components/Delegates/chatdelegate.h>
#include <Components/Dialogs/chatdialog.h>
#include <Components/Dialogs/showfollowings.h>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QListWidgetItem>
#include <QString>
#include <QUrl>

ChatComponent::ChatComponent(UserModel *model, QWidget *parent)
    : QWidget(parent), ui(new Ui::ChatComponent), socket(new QWebSocket),
      model(model) {
  ui->setupUi(this);

  /* init the web socket */
  connect(socket, &QWebSocket::connected, this, &ChatComponent::onConnected);
  connect(socket, &QWebSocket::disconnected, this,
          &ChatComponent::onDisconnected);
  connect(socket, &QWebSocket::textMessageReceived, this,
          &ChatComponent::textMessageReceived);
  connect(
      socket,
      QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::errorOccurred),
      this, &ChatComponent::onError);
  /* end the web socket handlers initialiization */

  socket->open(
      QUrl(QString("ws://localhost:3000/chat?user_id=%1").arg(model->getId())));
  ChatDialog::setGlobalUser(model);
}

ChatComponent::~ChatComponent() {
  delete ui;
  delete socket;
}

void ChatComponent::onConnected() { qDebug() << "connected to server"; }

void ChatComponent::onDisconnected() { qDebug() << "server disconnected!"; }

void ChatComponent::onError(QAbstractSocket::SocketError err) {
  qDebug() << "Error occured: " << err;
}

void ChatComponent::textMessageReceived(QString message) {
  QJsonDocument doc(QJsonDocument::fromJson(message.toUtf8()));
  QJsonObject json = doc.object();
  if (json["type"].toString() == "init") {
    QJsonArray chats = json["data"].toArray();
    for (const QJsonValue &value : chats)
      addChat(value.toInt());
  }
}

void ChatComponent::addChat(int id) {
  auto item = new QListWidgetItem();
  auto chat_delegate = new ChatDelegate(id);
  item->setSizeHint(chat_delegate->sizeHint());
  ui->Chats_list->addItem(item);
  ui->Chats_list->setItemWidget(item, chat_delegate);
}

void ChatComponent::on_startChatBtn_clicked() {
  ShowFollowings show_followings_dialog(model, this);
  show_followings_dialog.exec();
}
