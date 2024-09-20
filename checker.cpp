#include "checker.h"

Checker::Checker(const QColor& color, Cell* parent)
: QGraphicsEllipseItem(reinterpret_cast<QGraphicsItem*>(parent))
, cell_(parent) {
    setBrush(QBrush(color));
    changeCell(cell_);
}

void Checker::changeCell(Cell* cell) {
    cell_ = cell;
    const auto& pos = cell_->getPos();
    setRect(pos.first * 50 + 5, pos.second * 50 + 5, 40, 40);
    setParentItem(reinterpret_cast<QGraphicsItem*>(cell_));

    if (isKing_) {
        kingMark_->setRect(pos.first * 50 + 15, pos.second * 50 + 15, 20, 20);
    }
}

const QColor& Checker::getColor() const {
    return brush().color();
}

bool Checker::isKing() const {
    return isKing_;
}

void Checker::makeKing() {
    isKing_ = true;
    const auto& pos = cell_->getPos();
    kingMark_ = new QGraphicsEllipseItem(pos.first * 50 + 15, pos.second * 50 + 15, 20, 20, this);
    kingMark_->setBrush(QBrush(Color::blue));
}
