#include "loginsignin.h"
#include "ui_loginsignin.h"
#include <QTabBar>

LoginSignIn::LoginSignIn(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginSignIn)
{
    QPixmap icon(":/ico-cap-light.png");
    ui->setupUi(this);
    ui->IconImageViewer->setPixmap(icon);
}

LoginSignIn::~LoginSignIn()
{
    delete ui;
}
