#pragma once

#include <QString>

struct PlayerInfo {
    QString nickname;
    int rating;
    QString newNickname;
    QString enemyNickname;
    int enemyRating;
    QColor color;
};
