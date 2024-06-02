#include "homecomponent.h"

#include "ui_homecomponent.h"

HomeComponent::HomeComponent(QWidget *parent)
    : QWidget(parent), ui(new Ui::HomeComponent) {
  ui->setupUi(this);
  startPost_action = ui->StartPost_textBox->addAction(
      QIcon(QPixmap(":/arrow-right.png")), QLineEdit::TrailingPosition);
  connect(startPost_action, &QAction::triggered,
          [] { qDebug() << "Action Toggled"; });
}

HomeComponent::~HomeComponent() { delete ui; }
