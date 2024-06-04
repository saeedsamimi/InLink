#ifndef UTIL_H
#define UTIL_H

#include <QApplication>
#include <QString>
#include <QTranslator>
#include <QWidget>

class util {
 private:
  const static QString COLORED_TEXT_TEMPLATE;

 public:
  static QString buildColoredLabeled(QString label, QString color,
                                     QString content);
};

void enableStyle(QWidget* widget, const QString&& filename);

QTranslator* installTranslator(QApplication* app);
#endif  // UTIL_H
