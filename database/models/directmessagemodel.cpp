#include "directmessagemodel.h"

DirectMessageModel::DirectMessageModel(int msg_id, int who_id, int sender_id,
                                       Time time_sent, QString content,
                                       QPixmap picture)
    : ContentModel(sender_id, time_sent, content, picture), message_id(msg_id),
      who_id(who_id) {}
