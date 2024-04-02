#ifndef CODEVERIFIERLAYOUT_H
#define CODEVERIFIERLAYOUT_H

#include <Pages/verifycodedialog.h>

#include <QObject>
#include <QWidget>
#include <QtWidgets/QHBoxLayout>

#include "codeverifyedit.h"

class CodeVerifierLayout : public QWidget {
  Q_OBJECT
 public:
  explicit CodeVerifierLayout(QWidget *parent = nullptr);

  QString getText();

  ~CodeVerifierLayout();

 signals:
  void onAccepted();

 private slots:
  void onBoxFilled(uchar index);
  void onBoxCleared(uchar index);

 private:
  CodeVerifyEdit boxes[4];
  QHBoxLayout layout;
  VerifyCodeDialog dialog;

  void setupUI();
};

#endif  // CODEVERIFIERLAYOUT_H
