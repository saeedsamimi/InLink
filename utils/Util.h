#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QWidget>
#include <QApplication>
#include <QTranslator>

void enableStyle(QWidget* widget,const QString&& filename);

QTranslator *installTranslator(QApplication *app);

#endif // UTIL_H
