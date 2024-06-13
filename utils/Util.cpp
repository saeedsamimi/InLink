#include "Util.h"

#include <QFile>
#include <QIODevice>

void util::enableStyle(QWidget *widget, const QString &&filename) {
  QString prefix(":/qss/");
  QFile styleFile(prefix.append(filename));
  styleFile.open(QIODevice::ReadOnly | QIODevice::Text);
  QString styleString(styleFile.readAll());
  widget->setStyleSheet(styleString);
  styleFile.close();
}

QTranslator *util::installTranslator(QApplication *app) {
  QTranslator *translator = new QTranslator();
  Q_UNUSED(translator->load("InLink_en_US"));
  app->installTranslator(translator);
  return translator;
}

const QString util::COLORED_TEXT_TEMPLATE(
    R"(<p><span style="color: #%1">%2:</span> %3</p>)");

QString util::buildColoredLabeled(QString label, QString color,
                                  QString content) {
  return COLORED_TEXT_TEMPLATE.arg(color, label, content);
}

QString util::formatArray(const QStringList &list) {
  QString result;
  for (int i = 0; i < list.size(); ++i) {
    result += "\'" + list[i] + "\'";
    if (i + 1 < list.size())
      result += ",";
  }
  return result;
}
