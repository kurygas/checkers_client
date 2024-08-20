#pragma once
#include <QGraphicsRectItem>
#include <QBrush>
#include "checker.h"
#include "board.h"

class Board;

class Cell : public QGraphicsRectItem {
public:
    using Pos = QPair<int, int>;

    Cell(const Pos& pos, Board* board);
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    Checker* GetChecker();
    void SetChosen();
    void SetToMove();
    void SetToBeat();
    void ResetColor();
    bool ToMove() const;
    void SetChecker(Checker* checker);
    const Pos& GetPos() const;
    void RemoveChecker();

private:
    const Pos pos_;
    const QColor color_;
    Checker* checker_ = nullptr;
    Board* board_ = nullptr;
};
