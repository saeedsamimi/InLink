#include "whois.h"
#include "ui_whois.h"

WhoIs::WhoIs(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WhoIs)
{
    ui->setupUi(this);
}

WhoIs::~WhoIs()
{
    delete ui;
}
