#include "like.h"

Like::Like(const QString &like_id, const QString &liked_id,
           const QDateTime &time_liked)
    : like_id(like_id), liked_id(liked_id), time_liked(time_liked) {}

QString Like::getLikedId() const { return like_id; }

QString Like::getWhoLikedId() const { return liked_id; }

QDateTime Like::getTimeLiked() const { return time_liked; }

void Like::setLikedId(const QString &newID) { like_id = newID; }

void Like::setWhoLikedId(const QString &newID) { liked_id = newID; }

void Like::setTimeLiked(const QDateTime &newTime) { time_liked = newTime; }
