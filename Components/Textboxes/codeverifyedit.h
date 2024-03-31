#ifndef CODEVERIFYEDIT_H
#define CODEVERIFYEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QWidget>

class CodeVerifyEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(uchar index READ getIndex WRITE setIndex CONSTANT)
public:
    CodeVerifyEdit(QWidget *parent = nullptr);

    void setIndex(uchar);
    uchar getIndex();

signals:
    void filled(uchar index);
    void cleared(uchar index);


protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    uchar index;
};

#endif // CODEVERIFYEDIT_H
