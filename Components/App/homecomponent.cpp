#include "homecomponent.h"

#include <Components/Delegates/postwidget.h>

#include "ui_homecomponent.h"

HomeComponent::HomeComponent(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::HomeComponent),
      posts(std::move(PostModel::getAllPosts())) {
  ui->setupUi(this);
  startPost_action = ui->StartPost_textBox->addAction(
      QIcon(QPixmap(":/arrow-right.png")), QLineEdit::TrailingPosition);
  connect(startPost_action, &QAction::triggered,
          [] { qDebug() << "Action Toggled"; });
  for (auto item : posts) {
    auto widget_item = new QListWidgetItem();
    auto custom_widget = new PostWidget(item);
    widget_item->setSizeHint(custom_widget->sizeHint());
    ui->Feed->addItem(widget_item);
    ui->Feed->setItemWidget(widget_item, custom_widget);
  }
}

HomeComponent::~HomeComponent() { delete ui; }
