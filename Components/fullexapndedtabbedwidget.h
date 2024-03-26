#ifndef FULLEXAPNDEDTABBEDWIDGET_H
#define FULLEXAPNDEDTABBEDWIDGET_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>
#include <QTabBar>
#include <QResizeEvent>
#include <QFile>
#include <QStyle>
#include <QIODevice>

class FullExapndedTabbedWidget : public QTabWidget
{
    Q_OBJECT

    class TabBar : public QTabBar
    {
        QSize _size;
    public:
        TabBar(QWidget*);
        QSize tabSizeHint(int) const;
        void setWidth(int);
    };
public:
    FullExapndedTabbedWidget(QWidget*parent = nullptr);

    ~FullExapndedTabbedWidget();

    void resizeEvent(QResizeEvent *) override;
private:
    TabBar *tabBar;
};

#endif // FULLEXAPNDEDTABBEDWIDGET_H
