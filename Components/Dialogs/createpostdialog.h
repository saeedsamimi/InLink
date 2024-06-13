#ifndef CREATEPOSTDIALOG_H
#define CREATEPOSTDIALOG_H

#include <QDialog>
#include <database/models/postmodel.h>
#include <database/models/usermodel.h>

namespace Ui {
class CreatePostDialog;
}

class CreatePostDialog : public QDialog {
  Q_OBJECT

public:
  explicit CreatePostDialog(UserModel *model, QWidget *parent = nullptr);
  ~CreatePostDialog();

signals:
  void postCreated(PostModel model);

private slots:
  void on_CreatePostDialog_accepted();

  void on_select_pic_clicked();

private:
  Ui::CreatePostDialog *ui;
  UserModel *model;
  QPixmap img;
};

#endif // CREATEPOSTDIALOG_H
