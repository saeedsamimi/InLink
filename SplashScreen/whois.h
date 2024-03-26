#ifndef WHOIS_H
#define WHOIS_H

#include <QWidget>

namespace Ui {
class WhoIs;
}

class WhoIs : public QWidget
{
    Q_OBJECT

public:
    explicit WhoIs(QWidget *parent = nullptr);
    ~WhoIs();

private:
    Ui::WhoIs *ui;
};

#endif // WHOIS_H
