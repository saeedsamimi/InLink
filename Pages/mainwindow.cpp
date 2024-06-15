#include "mainwindow.h"

#include <utils/Util.h>

#include <QPushButton>

#include "ui_mainwindow.h"

MainWindow::MainWindow(UserModel model, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_user(model),
      me_component(new MeComponent(&m_user)),
      home_component(new HomeComponent(&m_user)),
      user_net_component(new UserNetworkComponent()),
      chat_component(new ChatComponent(&m_user)),
      jobs_component(new JobsComponent()), current_index(0) {
  ui->setupUi(this);

  stackedLayout = new QStackedLayout();
  ui->scrollAreaWidgetContents->setLayout(stackedLayout);

  /* initializing the Buttons Group */

  ui->tabsButtonGroup->addButton(ui->MeTabBtn, 4);
  ui->tabsButtonGroup->addButton(ui->messaginTabBtn, 3);
  ui->tabsButtonGroup->addButton(ui->JobsTabBtn, 2);
  ui->tabsButtonGroup->addButton(ui->MyNetworkTabBtn, 1);
  ui->tabsButtonGroup->addButton(ui->homeTabBtn, 0);

  /* load and enable style */

  util::enableStyle(this, "MW.qss");

  /* set the 0 button for the default first-selected item */

  ui->tabsButtonGroup->button(current_index)
      ->setStyleSheet("qproperty-iconSize: 24px;");

  /* enabling the search box icon action */

  QAction *searchAction = ui->SearchBoxTabButton->addAction(
      QIcon(QPixmap(":/search.svg")), QLineEdit::TrailingPosition);

  /* initializing the stacked layout widgets! */

  stackedLayout->addWidget(home_component);
  stackedLayout->addWidget(user_net_component);
  stackedLayout->addWidget(jobs_component);
  stackedLayout->addWidget(chat_component);
  stackedLayout->addWidget(me_component);

  /* connect the slots :
   * 1- logout handler
   * 2- search action handler
   * 3- change current button handler(s)!
   */

  connect(me_component, &MeComponent::logout, this, &MainWindow::handleLogOut);

  connect(searchAction, &QAction::triggered, this,
          &MainWindow::handleSearchBox);

  connect(ui->tabsButtonGroup, &QButtonGroup::idClicked, this,
          &MainWindow::handleChangeTab);
  connect(ui->tabsButtonGroup, &QButtonGroup::idClicked, stackedLayout,
          &QStackedLayout::setCurrentIndex);
}

MainWindow::~MainWindow() {
  delete ui;
  delete stackedLayout;
  delete me_component;
  delete home_component;
  delete user_net_component;
  delete chat_component;
  delete jobs_component;
}

void MainWindow::handleSearchBox() { qDebug() << "Unhandled search box"; }

void MainWindow::handleLogOut() {
  qDebug() << "handle logout in mainwindow called";
  this->close();
}

void MainWindow::handleChangeTab(int id) {
  /* change the styles of the current and previuos(current_next) buttons styles
   */

  ui->tabsButtonGroup->button(current_index)
      ->setStyleSheet("qproperty-iconSize: 10px;");
  current_index = id;
  ui->tabsButtonGroup->button(current_index)
      ->setStyleSheet("qproperty-iconSize: 24px;");
}
