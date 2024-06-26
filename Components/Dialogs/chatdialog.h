#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <Components/Delegates/messagedelegate.h>
#include <QDateTime>
#include <QDialog>
#include <QWebSocket>
#include <database/models/usermodel.h>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog {
  Q_OBJECT

public:
  explicit ChatDialog(UserModel *model, QWidget *parent = nullptr);
  ~ChatDialog();

  static void setGlobalUser(UserModel *model);

private:
  Ui::ChatDialog *ui;
  UserModel *model;
  QWebSocket *socket;
  static UserModel *globalUser;

  void addMessage(int sender, QString content, QDateTime time);
private slots:
  void textMessageReceived(QString message);
  void handleClickSendAction(bool);
  void on_sendBtn_clicked();
};

#endif // CHATDIALOG_H
