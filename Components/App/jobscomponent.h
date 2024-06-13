#ifndef JOBSCOMPONENT_H
#define JOBSCOMPONENT_H

#include <QWidget>

namespace Ui {
class JobsComponent;
}

class JobsComponent : public QWidget
{
    Q_OBJECT

public:
    explicit JobsComponent(QWidget *parent = nullptr);
    ~JobsComponent();

private:
    Ui::JobsComponent *ui;
};

#endif // JOBSCOMPONENT_H
