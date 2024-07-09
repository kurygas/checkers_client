#pragma once
#include <QString>

class PlayerInfo {
public:
    [[nodiscard]] const QString& GetNickname() const;
    void SetNickname(const QString& newNickname);
    [[nodiscard]] int GetRating() const;
    void SetRating(int newRating);

private:
    QString nickname_ = "$";
    int rating_ = 0;
};
