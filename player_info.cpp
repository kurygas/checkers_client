#include "player_info.h"

const QString& PlayerInfo::GetNickname() const {
    return nickname_;
}

void PlayerInfo::SetNickname(const QString& newNickname) {
    nickname_ = newNickname;
}

int PlayerInfo::GetRating() const {
    return rating_;
}

void PlayerInfo::SetRating(int newRating) {
    rating_ = newRating;
}
