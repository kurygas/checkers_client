#pragma once

#include <QString>

#include "friend_info.h"

struct PlayerInfo {
    QString nickname;
    int rating;
    QString newNickname;
    QString enemyNickname;
    int enemyRating;
    QColor color;
    QList<FriendInfo> friendList;
};
