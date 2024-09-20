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

    void changeCell(Cell* cell);
    void makeKing();

    const QColor& getColor() const;
    bool isKing() const;

private:
    bool isKing_ = false;
    Cell* cell_;
    QGraphicsEllipseItem* kingMark_ = nullptr;
};
