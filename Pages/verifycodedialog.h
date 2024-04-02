#ifndef VERIFYCODEDIALOG_H
#define VERIFYCODEDIALOG_H

#include <QDialog>

namespace Ui {
class VerifyCodeDialog;
}

class VerifyCodeDialog : public QDialog {
  Q_OBJECT

 public:
  explicit VerifyCodeDialog(QWidget *parent = nullptr);
  ~VerifyCodeDialog();

  void randomize();
  bool validate(const QString &text);

 private:
  Ui::VerifyCodeDialog *ui;
};

#endif  // VERIFYCODEDIALOG_H
