#include "player_info.h"

const QString& PlayerInfo::GetNickname() const {
    return nickname_;
}

void PlayerInfo::SetNickname(const QString& newNickname) {
    nickname_ = newNickname;
}

uint PlayerInfo::GetRating() const {
    return rating_;
}

void PlayerInfo::SetRating(const uint newRating) {
    rating_ = newRating;
}

void PlayerInfo::SetEnemy(const QString& nickname, const uint rating) {
    enemyNickname_ = nickname;
    enemyRating_ = rating;
}

const QString& PlayerInfo::GetEnemyNickname() const {
    return enemyNickname_;
}

uint PlayerInfo::GetEnemyRating() const {
    return enemyRating_;
}

bool PlayerInfo::HasEnemy() const {
    return !enemyNickname_.isEmpty();
}

void PlayerInfo::SetSearch(const bool state) {
    inSearch_ = state;
}

bool PlayerInfo::InSearch() const {
    return inSearch_;
}
