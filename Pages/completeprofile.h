#ifndef COMPLETEPROFILE_H
#define COMPLETEPROFILE_H

#include <QWidget>
#include <QSqlQuery>
#include <utils/preventclosingeventfilter.h>

namespace Ui {
class CompleteProfile;
}

class CompleteProfile : public QWidget
{
    Q_OBJECT

public:
    explicit CompleteProfile(int ID,QWidget *parent = nullptr);
    ~CompleteProfile();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onCloseRequested();

    void on_continueBtn_clicked();

private:
    Ui::CompleteProfile *ui;
    PreventClosingEventFilter closeFilter;
    QSqlQuery query;
    int ID;
};

#endif // COMPLETEPROFILE_H
