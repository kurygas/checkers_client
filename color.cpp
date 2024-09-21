#include "color.h"

QColor Color::negative(const QColor& color) {
    return {255 - color.red(), 255 - color.green(), 255 - color.blue()};
}
