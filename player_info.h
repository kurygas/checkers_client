#pragma once
#include <QString>

class PlayerInfo {
public:
    const QString& GetNickname() const;
    void SetNickname(const QString& newNickname);
    uint GetRating() const;
    void SetRating(uint newRating);
    void SetEnemy(const QString& nickname, uint rating);
    const QString& GetEnemyNickname() const;
    uint GetEnemyRating() const;
    bool HasEnemy() const;
    void SetSearch(bool state);
    bool InSearch() const;

private:
    QString nickname_;
    uint rating_ = 0;
    QString enemyNickname_;
    uint enemyRating_ = 0;
    bool inSearch_ = false;
};
