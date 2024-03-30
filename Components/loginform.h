#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QString>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT
public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

    QPair<QString,QString> getUser() const;
private:
    Ui::LoginForm *ui;
    QAction *eyeAction;
    QPixmap hideLogo,showLogo;

private slots:
    void passwordVisibilityChanged();
};

#endif // LOGINFORM_H
