#ifndef LIKES_H
#define LIKES_H
#include <Components/Buttons/iconbadges.h>
#include <QList>
#include <QListView>
#include <QObject>
#include <database/models/usermodel.h>

class Likes : public QObject {
  Q_OBJECT
public:
  Likes() = default;
  Likes(const Likes &);

  static Likes fromPost(const PostModel &post);
  void syncWithWidget(IconBadges *icon_badges);
  void syncWithView(QListView *view);

  qsizetype count() const;
  void pushUser(UserModel *model);
  void popUser(UserModel *model);

signals:
  void userPushUp(UserModel *model);
  void lastUserPop();

private:
  QList<UserModel> users;
};

#endif // LIKES_H
