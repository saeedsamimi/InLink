#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <loginsignin.h>
#include <utils/Util.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPixmap iconPic(":/ico-cap-light.png");
    QPixmap womanPic(":/sp-woman.png");
    QPixmap footerPic(":/city-footer.png");
    ui->setupUi(this);
    enableStyle(this,"SS.qss");
    ui->IconBox->setPixmap(iconPic);
    ui->WomanPicImageViewer->setPixmap(womanPic);
    ui->FooterPic->setPixmap(footerPic);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete loginPage;
}

void MainWindow::on_SignInBtn_clicked()
{
    loginPage = new LoginSignIn();
    qDebug() << "the SignInBtn in main window clicked! the login page will be show!!!";
    loginPage->show();
    close();
}
