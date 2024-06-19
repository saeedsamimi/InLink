#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <Pages/loginsignin.h>

#include <QLabel>
#include <QMainWindow>
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui {
class SplashScreen;
}
QT_END_NAMESPACE

class SplashScreen : public QMainWindow {
  Q_OBJECT

public:
  SplashScreen(QWidget *parent = nullptr);
  ~SplashScreen();
private slots:
  void on_SignInBtn_clicked();
  void on_LoginBtn_clicked();

private:
  Ui::SplashScreen *ui;
  QLabel *FindCourceLbl;
  LoginSignIn *loginPage;
};
#endif // SPLASHSCREEN_H
