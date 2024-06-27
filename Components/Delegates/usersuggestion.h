#ifndef USERSUGGESTION_H
#define USERSUGGESTION_H

#include <QWidget>
#include <database/models/usermodel.h>

namespace Ui {
class UserSuggestion;
}

class UserSuggestion : public QWidget {
  Q_OBJECT

public:
  explicit UserSuggestion(bool isCompany, const UserModel &model,
                          QWidget *parent = nullptr);
  ~UserSuggestion();

signals:
  void onClosed();
  void onFollow();

private slots:
  void on_close_btn_clicked();

  void on_follow_btn_clicked();

private:
  Ui::UserSuggestion *ui;
  UserModel model;
};

#endif // USERSUGGESTION_H
