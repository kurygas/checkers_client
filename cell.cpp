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
            checker_ = new Checker(Color::white, this);
        } else if (pos_.second > 4) {
            checker_ = new Checker(Color::black, this);
        }
    }
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    board_->cellPressed(pos_);
}

void Cell::setChosen() {
    setBrush(Color::green);
}

Checker* Cell::getChecker() {
    return checker_;
}

void Cell::setToMove() {
    setBrush(Color::yellow);
}

bool Cell::toMove() const {
    return brush().color() == Color::yellow;
}

bool Cell::toBeat() const {
    return brush().color() == Color::red;
}

void Cell::setToBeat() {
    setBrush(Color::red);
}

void Cell::resetColor() {
    setBrush(color_);
}

void Cell::setChecker(Checker* checker) {
    checker_ = checker;
    checker->changeCell(this);
}

const Pos& Cell::getPos() const {
    return pos_;
}

void Cell::releaseChecker() {
    checker_ = nullptr;
}

void Cell::removeChecker() {
    delete checker_;
    checker_ = nullptr;
}
