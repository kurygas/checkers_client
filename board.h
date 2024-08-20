#pragma once
#include <QGraphicsView>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <optional>
#include "cell.h"
#include "color.h"
#include "game_window.h"
#include "checker.h"

class Cell;
class GameWindow;
class Checker;

class Board : public QGraphicsView {
public:
    using Pos = QPair<int, int>;

    Board(QWidget* parent, const QColor& playerColor, GameWindow* gameWindow);
    void CellPressed(const Pos& pos);

private:
    Cell* GetCell(const Pos& pos);
    Checker* GetChecker(const Pos& pos);
    bool CanBeatOther(const Pos& pos);
    bool HaveBeatingMove();
    void ShowAllMoves(const Pos& pos);
    void ShowBeatingMoves(const Pos& pos);
    void ResetCells();
    QList<Board::Pos> PosToBeat(const Pos& pos);

    QGraphicsScene scene_;
    std::optional<Pos> chosenPos_;
    QList<QList<Cell*>> grid_;
    const QColor& playerColor_;
    GameWindow* gameWindow_;
};