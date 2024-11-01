#pragma once
#include <QString>

struct FriendInfo {
    enum class Status {
        Offline = 0,
        InLobby,
        InGame
    };

    QString nickname;
    Status status;
};