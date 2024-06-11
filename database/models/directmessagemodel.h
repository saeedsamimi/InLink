#ifndef DIRECTMESSAGEMODEL_H
#define DIRECTMESSAGEMODEL_H
#include <database/models/contentmodel.h>

class DirectMessageModel : ContentModel {
public:
  DirectMessageModel(int msg_id, int who_id, int sender_id, Time time_sent,
                     QString content, QPixmap picture);

private:
  int message_id;
  int who_id;
};

#endif // DIRECTMESSAGEMODEL_H
