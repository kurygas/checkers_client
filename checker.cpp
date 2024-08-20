#include "checker.h"

Checker::Checker(const QColor& color, Cell* parent)
: QGraphicsEllipseItem(reinterpret_cast<QGraphicsItem*>(parent)) {
    setBrush(QBrush(color));
    ChangeCell(parent);
}

void Checker::ChangeCell(Cell* cell) {
    const auto& pos = cell->GetPos();
    setRect(pos.first * 50 + 5, pos.second * 50 + 5, 40, 40);
    setParentItem(reinterpret_cast<QGraphicsItem*>(cell));
}

const QColor& Checker::GetColor() const {
    return brush().color();
}

bool Checker::IsKing() const {
    return isKing_;
}

void Checker::MakeKing() {
    isKing_ = true;
}
