#pragma once
#include <QGraphicsView>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <optional>
#include "cell.h"
#include "color.h"

class Cell;

class Board : public QGraphicsView {
public:
    Board(QWidget* parent, const QColor& playerColor);
    Cell* GetCell(const QPair<uint, uint>& pos);
    void CellPressed(const QPair<uint, uint>& pos);

private:
    QGraphicsScene scene_;
    std::optional<QPair<uint, uint>> chosenPos_;
    QList<QList<Cell*>> grid_;
    const QColor& playerColor_;
    bool myTurn_ = false;
};