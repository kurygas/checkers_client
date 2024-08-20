#pragma once
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include "cell.h"

class Cell;

class Checker : public QGraphicsEllipseItem {
public:
    using Pos = QPair<int, int>;

    Checker(const QColor& color, Cell* parent);
    void ChangeCell(Cell* cell);
    const QColor& GetColor() const;
    bool IsKing() const;
    void MakeKing();

private:
    bool isKing_ = false;
};
