#include "preventclosingeventfilter.h"
#include <QMessageBox>

PreventClosingEventFilter::PreventClosingEventFilter(QWidget *parent)
    : QObject{parent}
{}

void PreventClosingEventFilter::disable()
{
    disabled = true;
}

bool PreventClosingEventFilter::isDisabled(){
    return disabled;
}

bool PreventClosingEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::Close && !disabled){
        int res = QMessageBox::information(reinterpret_cast<QWidget*>(parent()),
                                           "Are you sure to exit?",
                                           "if you click \"yes\" your information will not save!",
                                           QMessageBox::No,QMessageBox::Yes);

        if(res == QMessageBox::No){
            event->ignore();
            return true;
        }
        emit onCloseRequested();
    }
    return QObject::eventFilter(obj,event);
}
