#include "cell.h"

Cell::Cell(const QPair<uint, uint>& pos, Board* board)
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

const QPair<uint, uint>& Cell::Pos() const {
    return pos_;
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    board_->CellPressed(pos_);
}

void Cell::SetChosen(const bool state) {
    setBrush(state ? QColor(218, 165, 32) : color_);
}

const Checker* Cell::GetChecker() const {
    return checker_;
}
