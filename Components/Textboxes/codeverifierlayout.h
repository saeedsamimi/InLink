#ifndef CODEVERIFIERLAYOUT_H
#define CODEVERIFIERLAYOUT_H

#include <QObject>
#include <QWidget>
#include <QtWidgets/QHBoxLayout>
#include <Pages/verifycodedialog.h>
#include "codeverifyedit.h"

class CodeVerifierLayout : public QWidget
{

    Q_OBJECT
public:
    explicit CodeVerifierLayout(QWidget *parent = nullptr);

    QString getText();

    ~CodeVerifierLayout();

signals:
    void onTextFinalized(const QString &code);

private slots:
    void onBoxFilled(uchar index);
    void onBoxCleared(uchar index);
    void onTextFinalizedSigned(const QString &);

private:
    CodeVerifyEdit boxes[4];
    QHBoxLayout layout;
    VerifyCodeDialog dialog;

    void setupUI();
};

#endif // CODEVERIFIERLAYOUT_H
