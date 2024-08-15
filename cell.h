#pragma once
#include <QGraphicsRectItem>
#include <QBrush>
#include "checker.h"
#include "board.h"

class Board;

class Cell : public QGraphicsRectItem {
public:
    explicit Cell(const QPair<uint, uint>& pos, Board* board);
    const QPair<uint, uint>& Pos() const;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void SetChosen(bool state);
    const Checker* GetChecker() const;

private:
    const QPair<uint, uint> pos_;
    const QColor color_;
    Checker* checker_ = nullptr;
    Board* board_ = nullptr;
};
