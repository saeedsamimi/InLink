#include "post.h"

Post::Post(const QString &post_id, const QString &sender_id,
           const QDateTime &time_sent, const QString &content_text,
           const QString &content_picture)
    : post_id(post_id), repost_counter(0),
      Content(sender_id, time_sent, content_text, content_picture) {}

QList<Comment> Post::getComments() const { return comments; }

QList<Like> Post::getLikes() const { return likes; }

void Post::addComment(const Comment &newComment) {
  comments.append(newComment);
}

void Post::addLike(const Like &newLike) { likes.append(newLike); }

void Post::removeLike(const QString &like_id) {
  likes.removeIf(
      [like_id](const Like &like) { return like.getLikedId() == like_id; });
}

Post Post::repost(const QString &user_id, Post &post) {
  Post new_post(post);
  new_post.setSenderId(user_id);
  post.repost_counter++;
  return new_post;
}
