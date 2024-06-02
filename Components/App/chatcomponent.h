#ifndef CHATCOMPONENT_H
#define CHATCOMPONENT_H

#include <QWidget>

namespace Ui {
class ChatComponent;
}

class ChatComponent : public QWidget
{
    Q_OBJECT

public:
    explicit ChatComponent(QWidget *parent = nullptr);
    ~ChatComponent();

private:
    Ui::ChatComponent *ui;
};

#endif // CHATCOMPONENT_H
