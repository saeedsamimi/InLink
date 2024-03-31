#ifndef CODEVERIFIER_H
#define CODEVERIFIER_H

#include <QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QString>

namespace Ui {
class CodeVerifier;
}

class CodeVerifier : public QWidget
{
    Q_OBJECT

public:
    explicit CodeVerifier(int ID,QWidget *parent = nullptr);
    ~CodeVerifier();

private slots:
    void on_widget_onAccepted();

private:
    Ui::CodeVerifier *ui;
    QLabel *msg;
    int ID;
};

#endif // CODEVERIFIER_H
