#include "Style.h"
#include <QFile>
#include <QIODevice>

void enableStyle(QWidget* widget,const QString&& filename){
    QString prefix(":/qss/");
    QFile styleFile(prefix.append(filename));
    styleFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString styleString (styleFile.readAll());
    widget->setStyleSheet(styleString);
    styleFile.close();
}
