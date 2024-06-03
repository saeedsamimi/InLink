#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <database/models/postmodel.h>

#include <QWidget>

namespace Ui {
class PostWidget;
}

class PostWidget : public QWidget {
  Q_OBJECT

 public:
  explicit PostWidget(const PostModel &text, QWidget *parent = nullptr);
  ~PostWidget();

 private:
  Ui::PostWidget *ui;
  PostModel model;
  UserModel owner;
};

#endif  // POSTWIDGET_H
