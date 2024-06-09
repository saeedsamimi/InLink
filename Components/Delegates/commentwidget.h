#ifndef COMMENTWIDGET_H
#define COMMENTWIDGET_H

#include <QWidget>
#include <database/models/postmodel.h>

namespace Ui {
class CommentWidget;
}

class CommentWidget : public QWidget {
  Q_OBJECT

public:
  explicit CommentWidget(Comment comment, QWidget *parent = nullptr);
  ~CommentWidget();

private:
  Ui::CommentWidget *ui;
  Comment comment;
};

#endif // COMMENTWIDGET_H
