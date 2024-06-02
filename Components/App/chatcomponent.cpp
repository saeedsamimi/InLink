#include "chatcomponent.h"
#include "ui_chatcomponent.h"

ChatComponent::ChatComponent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatComponent)
{
    ui->setupUi(this);
}

ChatComponent::~ChatComponent()
{
    delete ui;
}
