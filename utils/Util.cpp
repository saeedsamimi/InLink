#include "Util.h"

#include <QFile>
#include <QIODevice>

void enableStyle(QWidget *widget, const QString &&filename) {
  QString prefix(":/qss/");
  QFile styleFile(prefix.append(filename));
  styleFile.open(QIODevice::ReadOnly | QIODevice::Text);
  QString styleString(styleFile.readAll());
  widget->setStyleSheet(styleString);
  styleFile.close();
}

QTranslator *installTranslator(QApplication *app) {
  QTranslator *translator = new QTranslator();
  Q_UNUSED(translator->load("InLink_en_US"));
  app->installTranslator(translator);
  return translator;
}
