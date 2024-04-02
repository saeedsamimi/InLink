#include "codeverifier.h"

#include <database/user.h>
#include <utils/Util.h>

#include <QTimer>

#include "ui_codeverifier.h"

CodeVerifier::CodeVerifier(int ID, QWidget *parent)
    : QWidget(parent), ui(new Ui::CodeVerifier), ID(ID) {
  ui->setupUi(this);
  enableStyle(this, "PBS.qss");
}

CodeVerifier::~CodeVerifier() { delete ui; }

void CodeVerifier::on_widget_onAccepted() {
  try {
    qDebug() << "Accepted Successfully!";
    ui->verticalLayout->removeWidget(ui->widget);
    ui->widget->close();
    msg = new QLabel();
    msg->setPixmap(QPixmap(":/check.png"));
    ui->verticalLayout->addWidget(msg, 1, Qt::AlignCenter);
    changeAccountLevel(ID, UserLevel::Activated);
    complete = new CompleteProfile(ID);
    QTimer::singleShot(1000, complete, &CompleteProfile::show);
    QTimer::singleShot(1500, this, &CodeVerifier::close);
  } catch (QSqlError &err) {
    qDebug() << err;
  }
}
