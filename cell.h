#pragma once

#include <QGraphicsRectItem>
#include <QBrush>

#include "checker.h"
#include "board.h"
#include "pos.h"

class Board;

class Cell : public QGraphicsRectItem {
public:
    Cell(const Pos& pos, Board* board);

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    Checker* getChecker();
    void setChosen();
    void setToMove();
    void setToBeat();
    void resetColor();
    void setChecker(Checker* checker);
    void releaseChecker();
    void removeChecker();

    bool toMove() const;
    const Pos& getPos() const;
    bool toBeat() const;

private:
    const Pos pos_;
    const QColor color_;
    Checker* checker_ = nullptr;
    Board* board_ = nullptr;
};
