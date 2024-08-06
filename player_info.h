#pragma once
#include <QString>

struct PlayerInfo {
    QString nickname;
    uint rating = 0;
    QString enemyNickname;
    uint enemyRating = 0;
    bool inSearch = false;
    QString newNickname;
};