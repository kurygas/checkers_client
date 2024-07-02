#pragma once
#include <string>

class PlayerInfo {
public:
    [[nodiscard]] const std::string& GetNickname() const;
    void SetNickname(const std::string& newNickname);
    [[nodiscard]] int GetRating() const;
    void SetRating(int newRating);

private:
    std::string nickname_ = "$";
    int rating_ = 0;
};
