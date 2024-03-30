#include "splashscreen.h"
#include "ui_splashscreen.h"
#include <loginsignin.h>
#include <utils/Util.h>

SplashScreen::SplashScreen( QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SplashScreen)
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

SplashScreen::~SplashScreen()
{
    delete ui;
    delete loginPage;
}

void SplashScreen::on_SignInBtn_clicked()
{
    loginPage = new LoginSignIn();
    loginPage->show();
    close();
}

void SplashScreen::on_LoginBtn_clicked()
{
    loginPage = new LoginSignIn(true);
    loginPage->show();
    close();
}

