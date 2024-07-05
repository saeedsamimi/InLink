#include <main.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  auto translatorTemporary = util::installTranslator(&a);
  util::changeStyle(&a, util::Light);
  try {
    initDB();
  } catch (QSqlError &err) {
    QMessageBox::critical(
        nullptr, "connection failed",
        QString("Could not connect to the database because: %1")
            .arg(err.text()));
    a.exit(1);
    exit(1);
  }
  int id;
  int activationLevel;
  bool isLoggedIn = getActiveAccountUser(id, activationLevel);

  if (!isLoggedIn) {
    SplashScreen *splash = new SplashScreen();
    splash->show();
    splash->connect(splash, &SplashScreen::destroyed,
                    &SplashScreen::deleteLater);
  } else {
    LoaderWindow *loader = new LoaderWindow(id, activationLevel);
    loader->show();
    loader->connect(loader, &LoaderWindow::destroyed,
                    &LoaderWindow::deleteLater);
  }

  int exec = a.exec();
  delete translatorTemporary;
  return exec;
}
