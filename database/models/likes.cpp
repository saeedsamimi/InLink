#include "likes.h"
#include <QListView>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <database/models/postmodel.h>
#include <utils/Util.h>

// clang-format off
const QLatin1String getLikesSql("SELECT l.user_id FROM likes l JOIN users u ON u.id = l.user_id WHERE l.post_id = ?");
// clang-format on

Likes::Likes(const Likes &other) : users(std::move(other.users)) {}

Likes Likes::fromPost(const PostModel &post) {
  CREATE_SQL(getLikesSql);
  SQL_BIND(post.post_id);
  Likes res;
  if (!query.exec())
    SQL_THROW;
  while (query.next())
    res.users.emplace_back(query.value(0).toInt());
  return res;
}

void Likes::syncWithWidget(IconBadges *icon_badges) {
  int i;
  for (i = 0; i < 3 && i < users.length(); i++)
    icon_badges->setIcon(i, users[i].getUserProfile());
  for (; i < 3; i++)
    icon_badges->setIcon(
        i); // this will reset all unset or not setted pictures to null
  icon_badges->setCounterValue(users.size());
}

void Likes::syncWithView(QListView *view) {
  QStandardItemModel *model = new QStandardItemModel(view);
  for (auto &item : users)
    model->appendRow(
        new QStandardItem(QIcon(item.getUserProfile()),
                          item.getFirstName() + " " + item.getLastName()));
  view->setModel(model);
}

qsizetype Likes::count() const { return users.size(); }

void Likes::pushUser(UserModel *model) {
  users.push_back(*model);
  emit userPushUp(model);
}

void Likes::popUser(UserModel *model) {
  users.removeIf([model](const UserModel &item) { return item == *model; });
  emit lastUserPop();
}
