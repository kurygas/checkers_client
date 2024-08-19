#include "cell.h"

Cell::Cell(const Pos& pos, Board* board)
: QGraphicsRectItem(pos.first * 50, pos.second * 50, 50, 50)
, pos_(pos)
, color_((pos_.first + pos_.second) % 2 == 0 ? Color::beige : Color::brown)
, board_(board) {
    setAcceptedMouseButtons(Qt::LeftButton);
    setBrush(QBrush(color_));

    if (color_ == Color::brown) {
        if (pos_.second < 3) {
            checker_ = new Checker(Color::white, this, pos_);
        } else if (pos_.second > 4) {
            checker_ = new Checker(Color::black, this, pos_);
        }
    }
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    board_->CellPressed(pos_);
}

void Cell::SetChosen() {
    setBrush(Color::green);
}

Checker* Cell::GetChecker() {
    return checker_;
}

void Cell::SetToMove() {
    setBrush(Color::yellow);
}

bool Cell::ToMove() const {
    const auto currentColor = brush().color();
    return currentColor == Color::red || currentColor == Color::yellow;
}

void Cell::SetToBeat() {
    setBrush(Color::red);
}

void Cell::ResetColor() {
    setBrush(color_);
}
