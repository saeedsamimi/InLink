#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPixmap iconPic(":/ico-cap-light.png");
    QPixmap womanPic(":/sp-woman.png");
    QPixmap footerPic(":/city-footer.png");
    ui->setupUi(this);
    ui->IconBox->setPixmap(iconPic);
    ui->WomanPicImageViewer->setPixmap(womanPic);
    ui->FooterPic->setPixmap(footerPic);
}

MainWindow::~MainWindow()
{
    delete ui;
}
