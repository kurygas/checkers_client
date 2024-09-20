#pragma once

#include <QPair>

class Pos {
public:
    Pos& operator+=(const Pos& other);
    Pos operator+(const Pos& other) const;
    bool operator==(const Pos& other) const;
    bool operator!=(const Pos& other) const;
    Pos operator-(const Pos& other) const;

    void normalize();

    int first;
    int second;
};
