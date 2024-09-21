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

    void cellPressed(const Pos& pos);
    void moveChecker(const Pos& from, const Pos& to);
    Pos getBeatenPos(const Pos& pos1, const Pos& pos2);
    void removeChecker(const Pos& pos);

    const QColor& getPlayerColor() const;

private:
    Cell* getCell(const Pos& pos);
    Checker* getChecker(const Pos& pos);
    bool canBeatOther(const Pos& pos);
    bool haveBeatingMove();
    void showAllMoves(const Pos& pos);
    void showBeatingMoves(const Pos& pos);
    void resetCells();
    QList<Pos> posToBeat(const Pos& pos);

    static bool isValid(const Pos& pos);

    QGraphicsScene scene_;
    std::optional<Pos> chosenPos_;
    QList<QList<Cell*>> grid_;
    const QColor& playerColor_;
    GameWindow* gameWindow_;
    QList<QPair<Pos, Pos>> movesToSend_;
    int enemyCheckerCount_ = 12;
    const QList<Pos> moves_ = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
};
