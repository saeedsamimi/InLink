#ifndef CHATCOMPONENT_H
#define CHATCOMPONENT_H

#include <QWebSocket>
#include <QWidget>
#include <database/models/usermodel.h>

namespace Ui {
class ChatComponent;
}

class ChatComponent : public QWidget {
  Q_OBJECT

public:
  explicit ChatComponent(UserModel *model, QWidget *parent = nullptr);
  ~ChatComponent();

private slots:
  void onConnected();
  void onDisconnected();
  void onError(QAbstractSocket::SocketError err);
  void textMessageReceived(QString message);

  void on_startChatBtn_clicked();

  void on_retry_btn_clicked();

private:
  Ui::ChatComponent *ui;
  QWebSocket *socket;
  UserModel *model;

  void addChat(int id);
};

#endif // CHATCOMPONENT_H
