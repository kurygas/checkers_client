#pragma once
#include <QPair>

class Pos {
public:
    Pos& operator+=(const Pos& other);
    Pos operator+(const Pos& other) const;
    bool operator==(const Pos& other) const;
    bool operator!=(const Pos& other) const;
    void Normalize();
    Pos operator-(const Pos& other) const;

    int first;
    int second;
};
