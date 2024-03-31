#include "verifycodedialog.h"
#include "ui_verifycodedialog.h"
#include <QRandomGenerator>

VerifyCodeDialog::VerifyCodeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerifyCodeDialog)
{
    ui->setupUi(this);
    randomize();
}

VerifyCodeDialog::~VerifyCodeDialog()
{
    delete ui;
}

void VerifyCodeDialog::randomize()
{
    QRandomGenerator random;
    random = random.securelySeeded();
    auto res = random.bounded((quint32)1e3,(quint32)1e4-1);
    ui->code->setText(QString::asprintf("%4u",res));
}

bool VerifyCodeDialog::validate(const QString &text)
{
    return text.compare(ui->code->text()) == 0;
}
