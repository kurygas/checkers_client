#include "board.h"

Board::Board(QWidget* parent, const QColor& playerColor, GameWindow* gameWindow)
: QGraphicsView(parent)
, scene_(0, 0, 400, 400)
, grid_(8, QList<Cell*>(8, nullptr))
, playerColor_(playerColor)
, gameWindow_(gameWindow) {
    setScene(&scene_);

    for (auto i = 0; i < 8; ++i) {
        for (auto j = 0; j < 8; ++j) {
            grid_[j][i] = new Cell({j, i}, this);
            scene_.addItem(grid_[j][i]);
        }
    }
}

Cell* Board::getCell(const Pos& pos) {
    return grid_[pos.first][pos.second];
}

void Board::cellPressed(const Pos& pos) {
    if (!gameWindow_->isMyTurn()) {
        return;
    }

    if (pos == chosenPos_) {
        return;
    }

    auto* pressedCell = getCell(pos);

    if (pressedCell->toMove()) {
        const auto& checkerPos = chosenPos_.value();
        moveChecker(checkerPos, pos);
        movesToSend_.emplace_back(checkerPos, pos);
        resetCells();
        gameWindow_->sendMoves(movesToSend_);
        movesToSend_.clear();
    }
    else if (pressedCell->toBeat()) {
        const auto& checkerPos = chosenPos_.value();
        moveChecker(checkerPos, pos);
        movesToSend_.emplace_back(checkerPos, pos);
        resetCells();

        if (!posToBeat(pos).empty()) {
            chosenPos_ = pos;
            getCell(pos)->setChosen();
            showBeatingMoves(pos);
        }
        else {
            gameWindow_->sendMoves(movesToSend_);
            movesToSend_.clear();

            if (enemyCheckerCount_ == 11) {
                gameWindow_->sendMatchResult();
            }
        }
    }
    else {
        resetCells();

        if (getChecker(pos) && getChecker(pos)->getColor() == playerColor_) {
            chosenPos_ = pos;
            pressedCell->setChosen();

            if (haveBeatingMove()) {
                showBeatingMoves(pos);
            }
            else {
                showAllMoves(pos);
            }
        }
    }

}

Checker* Board::getChecker(const Pos& pos) {
    return getCell(pos)->getChecker();
}

bool Board::canBeatOther(const Pos& pos) {
    return !posToBeat(pos).empty();
}

bool Board::haveBeatingMove() {
    for (auto i = 0; i < 8; ++i) {
        for (auto j = 0; j < 8; ++j) {
            const auto* checker = getChecker({i, j});

            if (checker && checker->getColor() == playerColor_ && canBeatOther({i, j})) {
                return true;
            }
        }
    }

    return false;
}

void Board::showBeatingMoves(const Pos& pos) {
    for (const auto& move : posToBeat(pos)) {
        getCell(move)->setToBeat();
    }
}

void Board::showAllMoves(const Pos& pos) {
    showBeatingMoves(pos);

    if (getChecker(pos)->isKing()) {
        for (const auto& move : moves_) {
            for (Pos to = pos + move; isValid(to); to += move) {
                if (!getChecker(to)) {
                    getCell(to)->setToMove();
                }
                else {
                    break;
                }
            }
        }
    }
    else {
        for (const auto& move : moves_) {
            const auto to = pos + move;
            if (isValid(to) && !getChecker(to) && (move.second == 1 && playerColor_ == Color::white ||
            move.second == -1 && playerColor_ == Color::black)) {
                getCell(to)->setToMove();
            }
        }
    }
}

void Board::resetCells() {
    for (auto i = 0; i < 8; ++i) {
        for (auto j = 0; j < 8; ++j) {
            getCell({i, j})->resetColor();
        }
    }

    chosenPos_.reset();
}

QList<Pos> Board::posToBeat(const Pos& pos) {
    QList<Pos> result;

    if (getChecker(pos)->isKing()) {
        for (const auto& move : moves_) {
            bool metChecker = false;

            for (Pos to = pos + move; isValid(to); to += move) {
                const auto* checker = getChecker(to);

                if (checker) {
                    if (metChecker || checker->getColor() == playerColor_) {
                        break;
                    }
                    else {
                        metChecker = true;
                    }
                }
                else if (metChecker) {
                    result.emplace_back(to);
                }
            }
        }
    }
    else {
        for (const auto& move : moves_) {
            const auto to = pos + move;

            if (isValid(to + move)) {
                const auto* checker = getChecker(to);

                if (checker && !getChecker(to + move) && checker->getColor() != playerColor_) {
                    result.emplace_back(to + move);
                }
            }
        }
    }

    return result;
}

void Board::moveChecker(const Pos& from, const Pos& to) {
    getChecker(from)->changeCell(getCell(to));
    getCell(to)->setChecker(getChecker(from));
    getCell(from)->releaseChecker();
    const auto& color = getChecker(to)->getColor();

    if (to.second == 7 && color == Color::white || to.second == 0 && color == Color::black) {
        getChecker(to)->makeKing();
    }

    if (getChecker(getBeatenPos(from, to))) {
        removeChecker(getBeatenPos(from, to));
    }
}

Pos Board::getBeatenPos(const Pos& pos1, const Pos& pos2) {
    auto diff = pos1 - pos2;
    diff.normalize();

    for (Pos p = pos2 + diff; p != pos1; p += diff) {
        if (getChecker(p)) {
            return p;
        }
    }

    return {0, 0};
}

void Board::removeChecker(const Pos& pos) {
    if (getChecker(pos)->getColor() != playerColor_) {
        --enemyCheckerCount_;
    }

    getCell(pos)->removeChecker();
}

bool Board::isValid(const Pos& pos) {
    return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
}
