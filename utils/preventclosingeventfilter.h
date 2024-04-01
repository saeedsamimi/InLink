#ifndef PREVENTCLOSINGEVENTFILTER_H
#define PREVENTCLOSINGEVENTFILTER_H

#include <QObject>
#include <QWidget>
#include <QEvent>

class PreventClosingEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit PreventClosingEventFilter(QWidget *parent);

    void disable();

signals:
    void onCloseRequested();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    bool disabled = false;
};

#endif // PREVENTCLOSINGEVENTFILTER_H
