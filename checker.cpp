#include "checker.h"

Checker::Checker(const QColor& color, QGraphicsItem* parent, const QPair<uint, uint>& pos)
: QGraphicsEllipseItem(parent) {
    setBrush(QBrush(color));
    ChangePos(pos);
}

void Checker::ChangePos(const QPair<uint, uint>& pos) {
    setRect(pos.first * 50 + 5, pos.second * 50 + 5, 40, 40);
}

const QColor& Checker::GetColor() const {
    return brush().color();
}
