#include "jobscomponent.h"
#include "ui_jobscomponent.h"

JobsComponent::JobsComponent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JobsComponent)
{
    ui->setupUi(this);
}

JobsComponent::~JobsComponent()
{
    delete ui;
}
