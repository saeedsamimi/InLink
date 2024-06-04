#include "mainwindow.h"

#include <utils/Util.h>

#include <QPushButton>

#include "ui_mainwindow.h"

MainWindow::MainWindow(const UserModel &model, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_user(model),
      me_component(new MeComponent(&m_user)),
      home_component(new HomeComponent(&m_user)),
      user_net_component(new UserNetworkComponent()),
      chat_component(new ChatComponent()), jobs_component(new JobsComponent()) {
  ui->setupUi(this);
  stackedLayout = new QStackedLayout();
  ui->scrollAreaWidgetContents->setLayout(stackedLayout);
  buttons = new QButtonGroup();
  buttons->addButton(ui->MeTabBtn, 4);
  buttons->addButton(ui->messaginTabBtn, 3);
  buttons->addButton(ui->JobsTabBtn, 2);
  buttons->addButton(ui->MyNetworkTabBtn, 1);
  buttons->addButton(ui->homeTabBtn, 0);
  connect(buttons, QButtonGroup::idClicked, stackedLayout,
          &QStackedLayout::setCurrentIndex);
  enableStyle(this, "MW.qss");
  QAction *searchAction = ui->SearchBoxTabButton->addAction(
      QIcon(QPixmap(":/search.svg")), QLineEdit::TrailingPosition);
  connect(searchAction, &QAction::triggered, this,
          &MainWindow::handleSearchBox);
  stackedLayout->addWidget(home_component);
  stackedLayout->addWidget(user_net_component);
  stackedLayout->addWidget(jobs_component);
  stackedLayout->addWidget(chat_component);
  stackedLayout->addWidget(me_component);
}

MainWindow::~MainWindow() {
  delete ui;
  delete buttons;
  delete stackedLayout;
  delete me_component;
  delete home_component;
  delete user_net_component;
  delete chat_component;
  delete jobs_component;
}

void MainWindow::handleSearchBox() { qDebug() << "Unhandled search box"; }
