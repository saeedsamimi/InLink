#ifndef UTIL_H
#define UTIL_H

#include <QApplication>
#include <QSqlQuery>
#include <QString>
#include <QTranslator>
#include <QWidget>

class util {
private:
  const static QString COLORED_TEXT_TEMPLATE;

public:
  static QString buildColoredLabeled(QString label, QString color,
                                     QString content);
  static QString formatArray(const QStringList &list);
  static void enableStyle(QWidget *widget, const QString &&filename);
  static QTranslator *installTranslator(QApplication *app);
};

/* Util macros */

#define CREATE_SQL(x)                                                          \
  QSqlQuery query;                                                             \
  query.prepare(x)

#define SQL_BIND(x) query.addBindValue(x)
#define SQL_BIND_PLACED(x, y) query.bindValue(x, y)
#define SQL_THROW throw query.lastError()

#endif // UTIL_H
