#pragma once
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

class Checker : public QGraphicsEllipseItem {
public:
    using Pos = QPair<int, int>;

    Checker(const QColor& color, QGraphicsItem* parent, const Pos& pos);
    void ChangePos(const Pos& pos);
    const QColor& GetColor() const;
    bool IsKing() const;
    void MakeKing();

private:
    bool isKing_ = false;
};
