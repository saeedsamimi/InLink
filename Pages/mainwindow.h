#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Components/App/chatcomponent.h>
#include <Components/App/homecomponent.h>
#include <Components/App/mecomponent.h>
#include <Components/App/usernetworkcomponent.h>
#include <database/models/usermodel.h>

#include <QCompleter>
#include <QMainWindow>
#include <QStackedLayout>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
private:
  UserModel m_user;
  Q_OBJECT

public:
  explicit MainWindow(UserModel model, QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void handleLogOut();
  void handleChangeTab(int);

private:
  Ui::MainWindow *ui;
  QCompleter searchBoxCompleter;
  QStandardItemModel usersModel;
  QStackedLayout *stackedLayout;
  MeComponent *me_component;
  HomeComponent *home_component;
  UserNetworkComponent *user_net_component;
  ChatComponent *chat_component;
  QWidget *jobs_component;
  int current_index = 0;
};

#endif // MAINWINDOW_H
