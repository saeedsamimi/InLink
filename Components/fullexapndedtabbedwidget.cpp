#include "fullexapndedtabbedwidget.h"
#include <utils/Style.h>

FullExapndedTabbedWidget::FullExapndedTabbedWidget(QWidget *parent) : QTabWidget(parent),tabBar(new TabBar(this)){
    enableStyle(this,"FETW.qss");
    tabBar->setExpanding(true);
    setTabBar(tabBar);
}

FullExapndedTabbedWidget::~FullExapndedTabbedWidget()
{
    delete tabBar;
}

void FullExapndedTabbedWidget::resizeEvent(QResizeEvent *e)
{
    tabBar->setWidth(size().width());
    QTabWidget::resizeEvent(e);
}

FullExapndedTabbedWidget::TabBar::TabBar(QWidget *parent) :QTabBar(parent)
{
    setWidth(size().width());
}

QSize FullExapndedTabbedWidget::TabBar::tabSizeHint(int index) const
{
    return QSize(_size.width()/(count()?count():1), size().height());
}

void FullExapndedTabbedWidget::TabBar::setWidth(int a_width)
{
    _size = QSize(a_width, size().height());
    QTabBar::resize(_size);
}




