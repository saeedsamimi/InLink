#include "usernetworkcomponent.h"
#include "ui_usernetworkcomponent.h"

UserNetworkComponent::UserNetworkComponent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserNetworkComponent)
{
    ui->setupUi(this);
}

UserNetworkComponent::~UserNetworkComponent()
{
    delete ui;
}
