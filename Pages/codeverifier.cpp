#include "codeverifier.h"
#include "ui_codeverifier.h"
#include <utils/Util.h>

CodeVerifier::CodeVerifier(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CodeVerifier)
{
    ui->setupUi(this);
    enableStyle(this,"PBS.qss");
}

CodeVerifier::~CodeVerifier() {
    delete ui;
}
