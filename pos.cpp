#include "pos.h"

Pos& Pos::operator+=(const Pos& other) {
    first += other.first;
    second += other.second;
    return *this;
}

Pos Pos::operator+(const Pos& other) const {
    Pos result(*this);
    result += other;
    return result;
}

bool Pos::operator==(const Pos& other) const {
    return first == other.first && second == other.second;
}

void Pos::Normalize() {
    first /= std::abs(first);
    second /= std::abs(second);
}

Pos Pos::operator-(const Pos& other) const {
    return {first - other.first, second - other.second};
}

bool Pos::operator!=(const Pos& other) const {
    return !(*this == other);
}
