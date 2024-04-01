#include "completeprofile.h"
#include "ui_completeprofile.h"
#include <QMessageBox>
#include <utils/Util.h>
#include <QSqlQuery>

CompleteProfile::CompleteProfile(int ID,QWidget *parent)
    : QWidget(parent),ID(ID),query{},closeFilter(parent)
    , ui(new Ui::CompleteProfile)
{
    installEventFilter(&closeFilter);
    ui->setupUi(this);
    enableStyle(ui->continueBtn,"PBS.qss");
    enableStyle(this,"CPS.qss");
    query.exec("BEGIN TRANSACTION;");
    connect(&closeFilter,
            &PreventClosingEventFilter::onCloseRequested,
            this,
            &CompleteProfile::onCloseRequested);
}

CompleteProfile::~CompleteProfile()
{
    delete ui;
}

void CompleteProfile::closeEvent(QCloseEvent *event)
{
    if(!query.exec("COMMIT;"))
        QMessageBox::critical(nullptr,"Error", "The information not saved");
    QWidget::closeEvent(event);
}

void CompleteProfile::onCloseRequested()
{
    query.exec("ROLLBACK;");
}


void CompleteProfile::on_continueBtn_clicked()
{
    closeFilter.disable();
    close();
}

