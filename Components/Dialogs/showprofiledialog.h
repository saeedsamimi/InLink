#ifndef SHOWPROFILEDIALOG_H
#define SHOWPROFILEDIALOG_H

#include <Components/App/mecomponent.h>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>
#include <database/models/usermodel.h>

class ShowProfileDialogUi {
private:
  MeComponent *profile;
  QListWidget *posts;
  QGridLayout *layout;
  QLabel *posts_lbl;

public:
  void setupUi(UserModel *model, QDialog *parent);
  ~ShowProfileDialogUi();

  friend class ShowProfileDialog;
};

class ShowProfileDialog : public QDialog {
  Q_OBJECT

public:
  explicit ShowProfileDialog(UserModel *model, QWidget *parent = nullptr);
  ~ShowProfileDialog();

private:
  ShowProfileDialogUi *ui;
  UserModel *model;

  void addPost(PostModel &post);
};

#endif // SHOWPROFILEDIALOG_H
