#pragma once

#include <QColor>

namespace Color {
    constexpr QColor white = {255, 255, 255};
    constexpr QColor black = {0, 0, 0};
    constexpr QColor beige = {255, 222, 173};
    constexpr QColor brown = {160, 82, 45};
    constexpr QColor red = {255, 0, 0};
    constexpr QColor yellow = {255, 255, 0};
    constexpr QColor green = {0, 255, 0};
    constexpr QColor blue = {0, 0, 255};

    QColor negative(const QColor& color);
};
