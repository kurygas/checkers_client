#pragma once
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

class Checker : public QGraphicsEllipseItem {
public:
    Checker(const QColor& color, QGraphicsItem* parent, const QPair<uint, uint>& pos);
    void ChangePos(const QPair<uint, uint>& pos);
    const QColor& GetColor() const;
};
