#ifndef CODEVERIFIER_H
#define CODEVERIFIER_H

#include <QWidget>
#include <QtWidgets/QLineEdit>

namespace Ui {
class CodeVerifier;
}

class CodeVerifier : public QWidget
{
    Q_OBJECT

public:
    explicit CodeVerifier(QWidget *parent = nullptr);
    ~CodeVerifier();

private:
    Ui::CodeVerifier *ui;
};

#endif // CODEVERIFIER_H
