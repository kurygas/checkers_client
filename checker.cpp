#include "checker.h"

Checker::Checker(const QColor& color, Cell* parent)
: QGraphicsEllipseItem(reinterpret_cast<QGraphicsItem*>(parent))
, cell_(parent) {
    setBrush(QBrush(color));
    ChangeCell(cell_);
}

void Checker::ChangeCell(Cell* cell) {
    cell_ = cell;
    const auto& pos = cell_->GetPos();
    setRect(pos.first * 50 + 5, pos.second * 50 + 5, 40, 40);
    setParentItem(reinterpret_cast<QGraphicsItem*>(cell_));
    kingMark_->setRect(pos.first * 50 + 15, pos.second * 50 + 15, 20, 20);
}

const QColor& Checker::GetColor() const {
    return brush().color();
}

bool Checker::IsKing() const {
    return isKing_;
}

void Checker::MakeKing() {
    isKing_ = true;
    const auto& pos = cell_->GetPos();
    kingMark_ = new QGraphicsEllipseItem(pos.first * 50 + 15, pos.second * 50 + 15, 20, 20, this);
    kingMark_->setBrush(QBrush(Color::blue));
}
