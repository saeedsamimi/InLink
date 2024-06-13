#ifndef COMMENTSDIALOG_H
#define COMMENTSDIALOG_H

#include <Components/Delegates/postwidget.h>
#include <QDialog>
#include <database/models/postmodel.h>
#include <database/models/usermodel.h>

namespace Ui {
class CommentsDialog;
}

class CommentsDialog : public QDialog {
  Q_OBJECT

public:
  explicit CommentsDialog(UserModel *mode, const PostModel &post,
                          QWidget *parent = nullptr);
  ~CommentsDialog();

private slots:
  void handleClickCreateComment();

  void on_create_command_text_box_returnPressed();

private:
  Ui::CommentsDialog *ui;
  UserModel *user_model;
  PostModel post_model;
  PostWidget *post_widget;

  void addComment(Comment &comment);
};

#endif // COMMENTSDIALOG_H
