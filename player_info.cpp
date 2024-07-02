#include "player_info.h"

const std::string& PlayerInfo::GetNickname() const {
    return nickname_;
}

void PlayerInfo::SetNickname(const std::string& newNickname) {
    nickname_ = newNickname;
}

int PlayerInfo::GetRating() const {
    return rating_;
}

void PlayerInfo::SetRating(int newRating) {
    rating_ = newRating;
}
