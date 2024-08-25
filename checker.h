#pragma once
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include "cell.h"
#include "pos.h"

class Cell;

class Checker : public QGraphicsEllipseItem {
public:
    Checker(const QColor& color, Cell* parent);
    void ChangeCell(Cell* cell);
    const QColor& GetColor() const;
    bool IsKing() const;
    void MakeKing();

private:
    bool isKing_ = false;
    Cell* cell_;
    QGraphicsEllipseItem* kingMark_ = nullptr;
};
