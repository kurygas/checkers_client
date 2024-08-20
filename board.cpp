#include "board.h"

Board::Board(QWidget* parent, const QColor& playerColor, GameWindow* gameWindow)
: QGraphicsView(parent)
, scene_(0, 0, 400, 400)
, grid_(8, QList<Cell*>(8, nullptr))
, playerColor_(playerColor)
, gameWindow_(gameWindow) {
    setScene(&scene_);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            grid_[j][i] = new Cell({j, i}, this);
            scene_.addItem(grid_[j][i]);
        }
    }
}

Cell* Board::GetCell(const Pos& pos) {
    return grid_[pos.first][pos.second];
}

void Board::CellPressed(const Pos& pos) {
    if (!gameWindow_->IsMyTurn()) {
        return;
    }

    if (pos == chosenPos_) {
        return;
    }

    auto* pressedCell = GetCell(pos);

    if (pressedCell->ToMove()) {
        const auto& checkerPos = chosenPos_.value();
        MoveChecker(checkerPos, pos);
        movesToSend_.emplace_back(checkerPos, pos);
        ResetCells();
        gameWindow_->SendMoves(movesToSend_);
        movesToSend_.clear();
    }
    else if (pressedCell->ToBeat()) {
        --enemyCheckerCount;
        const auto& checkerPos = chosenPos_.value();
        MoveChecker(checkerPos, pos);
        RemoveChecker(GetMiddlePos(checkerPos, pos));
        movesToSend_.emplace_back(checkerPos, pos);
        ResetCells();

        if (!PosToBeat(pos).empty()) {
            chosenPos_ = pos;
            GetCell(pos)->SetChosen();
            ShowBeatingMoves(pos);
        }
        else {
            gameWindow_->SendMoves(movesToSend_);
            movesToSend_.clear();

            if (enemyCheckerCount == 0) {
                gameWindow_->SendMatchResult();
            }
        }
    }
    else {
        ResetCells();

        if (GetChecker(pos)) {
            chosenPos_ = pos;
            pressedCell->SetChosen();

            if (HaveBeatingMove()) {
                ShowBeatingMoves(pos);
            }
            else {
                ShowAllMoves(pos);
            }
        }
    }

}

Checker* Board::GetChecker(const Pos& pos) {
    return GetCell(pos)->GetChecker();
}

bool Board::CanBeatOther(const Pos& pos) {
    return !PosToBeat(pos).empty();
}

bool Board::HaveBeatingMove() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            const auto* checker = GetChecker({i, j});

            if (checker && checker->GetColor() == playerColor_ && CanBeatOther({i, j})) {
                return true;
            }
        }
    }

    return false;
}

void Board::ShowBeatingMoves(const Pos& pos) {
    for (const auto& move : PosToBeat(pos)) {
        GetCell(move)->SetToBeat();
    }
}

void Board::ShowAllMoves(const Pos& pos) {
    ShowBeatingMoves(pos);

    if (GetChecker(pos)->IsKing()) {
        for (int i = 1; pos.first + i < 8 && pos.second + i < 8; ++i) {
            if (!GetChecker({pos.first + i, pos.second + i})) {
                GetCell({pos.first + i, pos.second + i})->SetToMove();
            } else {
                break;
            }
        }

        for (int i = 1; pos.first + i < 8 && pos.second - i >= 0; ++i) {
            if (!GetChecker({pos.first + i, pos.second - i})) {
                GetCell({pos.first + i, pos.second - i})->SetToMove();
            } else {
                break;
            }
        }

        for (int i = 1; pos.first - i >= 0 && pos.second + i < 8; ++i) {
            if (!GetChecker({pos.first - i, pos.second + i})) {
                GetCell({pos.first - i, pos.second + i})->SetToMove();
            } else {
                break;
            }
        }

        for (int i = 1; pos.first - i >= 0 && pos.second - i >= 0; ++i) {
            if (!GetChecker({pos.first - i, pos.second - i})) {
                GetCell({pos.first - i, pos.second - i})->SetToMove();
            } else {
                break;
            }
        }
    }
    else {
        if (playerColor_ == Color::white) {
            if (pos.first + 1 < 8 && pos.second + 1 < 8 && !GetChecker({pos.first + 1, pos.second + 1})) {
                GetCell({pos.first + 1, pos.second + 1})->SetToMove();
            }

            if (pos.first + 1 < 8 && pos.second - 1 >= 0 && !GetChecker({pos.first + 1, pos.second - 1})) {
                GetCell({pos.first + 1, pos.second - 1})->SetToMove();
            }
        }
        else {
            if (pos.first - 1 >= 0 && pos.second + 1 < 8 && !GetChecker({pos.first - 1, pos.second + 1})) {
                GetCell({pos.first - 1, pos.second + 1})->SetToMove();
            }

            if (pos.first - 1 >= 0 && pos.second - 1 >= 0 && !GetChecker({pos.first - 1, pos.second - 1})) {
                GetCell({pos.first - 1, pos.second - 1})->SetToMove();
            }
        }
    }
}

void Board::ResetCells() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            GetCell({i, j})->ResetColor();
        }
    }

    chosenPos_.reset();
}

QList<Board::Pos> Board::PosToBeat(const Pos& pos) {
    QList<Pos> result;
    const Checker* checker;

    if (GetChecker(pos)->IsKing()) {
        for (int i = 1; pos.first + i + 1 < 8 && pos.second + i + 1 < 8; ++i) {
            checker = GetChecker({pos.first + i, pos.second + i});

            if (checker) {
                if (!GetChecker({pos.first + i + 1, pos.second + i + 1}) && checker->GetColor() != playerColor_) {
                    result.emplace_back(pos.first + i + 1, pos.second + i + 1);
                }
                else {
                    break;
                }
            }
        }

        for (int i = 1; pos.first + i + 1 < 8 && pos.second - i - 1 >= 0; ++i) {
            checker = GetChecker({pos.first + i, pos.second - i});

            if (checker) {
                if (!GetChecker({pos.first + i + 1, pos.second - i - 1}) && checker->GetColor() != playerColor_) {
                    result.emplace_back(pos.first + i + 1, pos.second - i - 1);
                }
                else {
                    break;
                }
            }
        }

        for (int i = 1; pos.first - i - 1 >= 0 && pos.second + i + 1 < 8; ++i) {
            checker = GetChecker({pos.first - i, pos.second + i});

            if (checker) {
                if (!GetChecker({pos.first - i - 1, pos.second + i + 1}) && checker->GetColor() != playerColor_) {
                    result.emplace_back(pos.first - i - 1, pos.second + i + 1);
                }
                else {
                    break;
                }
            }
        }

        for (int i = 1; pos.first - i - 1 >= 0 && pos.second - i - 1 >= 0; ++i) {
            checker = GetChecker({pos.first - i, pos.second - i});

            if (checker) {
                if (!GetChecker({pos.first - i - 1, pos.second - i - 1}) && checker->GetColor() != playerColor_) {
                    result.emplace_back(pos.first - i - 1, pos.second - i - 1);
                }
                else {
                    break;
                }
            }
        }
    }
    else {
        if (pos.first + 2 < 8 && pos.second + 2 < 8) {
            checker = GetChecker({pos.first + 1, pos.second + 1});

            if (checker && checker->GetColor() != playerColor_ && !GetChecker({pos.first + 2, pos.second + 2})) {
                result.emplace_back(pos.first + 2, pos.second + 2);
            }
        }

        if (pos.first + 2 < 8 && pos.second - 2 >= 0) {
            checker = GetChecker({pos.first + 1, pos.second - 1});

            if (checker && checker->GetColor() != playerColor_ && !GetChecker({pos.first + 2, pos.second - 2})) {
                result.emplace_back(pos.first + 2, pos.second - 2);
            }
        }

        if (pos.first - 2 >= 0 && pos.second + 2 < 8) {
            checker = GetChecker({pos.first - 1, pos.second + 1});

            if (checker && checker->GetColor() != playerColor_ && !GetChecker({pos.first - 2, pos.second + 2})) {
                result.emplace_back(pos.first - 2, pos.second + 2);
            }
        }

        if (pos.first - 2 >= 0 && pos.second - 2 >= 0) {
            checker = GetChecker({pos.first - 1, pos.second - 1});

            if (checker && checker->GetColor() != playerColor_ && !GetChecker({pos.first - 2, pos.second - 2})) {
                result.emplace_back(pos.first - 2, pos.second - 2);
            }
        }
    }

    return result;
}

void Board::MoveChecker(const Pos& from, const Pos& to) {
    GetChecker(from)->ChangeCell(GetCell(to));
    GetCell(from)->ReleaseChecker();
}

Board::Pos Board::GetMiddlePos(const Pos& pos1, const Pos& pos2) {
    return {(pos1.first + pos2.first) / 2, (pos1.second + pos2.second) / 2};
}

void Board::RemoveChecker(const Pos& pos) {
    if (GetChecker(pos)->GetColor() == playerColor_) {
        --playerCheckerCount;
    }
    else {
        --enemyCheckerCount;
    }

    GetCell(pos)->RemoveChecker();
}

uint Board::GetPlayerCount() const {
    return playerCheckerCount;
}
