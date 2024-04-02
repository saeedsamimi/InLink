#ifndef UTIL_H
#define UTIL_H

#include <QApplication>
#include <QString>
#include <QTranslator>
#include <QWidget>

void enableStyle(QWidget* widget, const QString&& filename);

QTranslator* installTranslator(QApplication* app);
#endif  // UTIL_H
