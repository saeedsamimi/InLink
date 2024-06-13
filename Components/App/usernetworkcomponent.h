#ifndef USERNETWORKCOMPONENT_H
#define USERNETWORKCOMPONENT_H

#include <QWidget>

namespace Ui {
class UserNetworkComponent;
}

class UserNetworkComponent : public QWidget
{
    Q_OBJECT

public:
    explicit UserNetworkComponent(QWidget *parent = nullptr);
    ~UserNetworkComponent();

private:
    Ui::UserNetworkComponent *ui;
};

#endif // USERNETWORKCOMPONENT_H
