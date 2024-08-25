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
    Board(QWidget* parent, const QColor& playerColor, GameWindow* gameWindow);
    void CellPressed(const Pos& pos);
    void MoveChecker(const Pos& from, const Pos& to);
    Pos GetBeatenPos(const Pos& pos1, const Pos& pos2);
    void RemoveChecker(const Pos& pos);

private:
    Cell* GetCell(const Pos& pos);
    Checker* GetChecker(const Pos& pos);
    bool CanBeatOther(const Pos& pos);
    bool HaveBeatingMove();
    void ShowAllMoves(const Pos& pos);
    void ShowBeatingMoves(const Pos& pos);
    void ResetCells();
    QList<Pos> PosToBeat(const Pos& pos);
    static bool IsValid(const Pos& pos);

    QGraphicsScene scene_;
    std::optional<Pos> chosenPos_;
    QList<QList<Cell*>> grid_;
    const QColor& playerColor_;
    GameWindow* gameWindow_;
    QList<QPair<Pos, Pos>> movesToSend_;
    uint enemyCheckerCount = 12;
    const QList<Pos> moves_ = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
};
