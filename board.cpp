#include "board.h"

Board::Board(QWidget* parent, const QColor& playerColor, const GameWindow* gameWindow)
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
        GetChecker(chosenPos_.value())->ChangePos(pos);
        chosenPos_.reset();
        ResetCells();
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

Checker* Board::GetChecker(const Board::Pos& pos) {
    return GetCell(pos)->GetChecker();
}

bool Board::CanBeatOther(const Pos& pos) {
    if (GetChecker(pos)->IsKing()) {
        for (int i = 1; pos.first + i + 1 < 8 && pos.second + i + 1 < 8; ++i) {
            if (GetChecker({pos.first + i, pos.second + i})) {
                if (!GetChecker({pos.first + i + 1, pos.second + i + 1})) {
                    return true;
                }
                else {
                    break;
                }
            }
        }

        for (int i = 1; pos.first + i + 1 < 8 && pos.second - i - 1 >= 0; ++i) {
            if (GetChecker({pos.first + i, pos.second - i})) {
                if (!GetChecker({pos.first + i + 1, pos.second - i - 1})) {
                    return true;
                }
                else {
                    break;
                }
            }
        }

        for (int i = 1; pos.first - i - 1 >= 0 && pos.second + i + 1 < 8; ++i) {
            if (GetChecker({pos.first - i, pos.second + i})) {
                if (!GetChecker({pos.first - i - 1, pos.second + i + 1})) {
                    return true;
                }
                else {
                    break;
                }
            }
        }

        for (int i = 1; pos.first - i - 1 >= 0 && pos.second - i - 1 >= 0; ++i) {
            if (GetChecker({pos.first - i, pos.second - i})) {
                if (!GetChecker({pos.first - i - 1, pos.second - i - 1})) {
                    return true;
                }
                else {
                    break;
                }
            }
        }
    }
    else {
        if (ValidPos({pos.first + 2, pos.second + 2}) &&
        GetChecker({pos.first + 1, pos.second + 1}) && !GetChecker({pos.first + 2, pos.second + 2})) {
            return true;
        }

        if (ValidPos({pos.first + 2, pos.second - 2}) &&
        GetChecker({pos.first + 1, pos.second - 1}) && !GetChecker({pos.first + 2, pos.second - 2})) {
            return true;
        }

        if (ValidPos({pos.first - 2, pos.second + 2}) &&
        GetChecker({pos.first - 1, pos.second + 1}) && !GetChecker({pos.first - 2, pos.second + 2})) {
            return true;
        }

        if (ValidPos({pos.first - 2, pos.second - 2}) &&
        GetChecker({pos.first - 1, pos.second - 1}) && !GetChecker({pos.first - 2, pos.second - 2})) {
            return true;
        }
    }

    return false;
}

bool Board::HaveBeatingMove() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (GetChecker({i, j}) && CanBeatOther({i, j})) {
                return true;
            }
        }
    }

    return false;
}

void Board::ShowBeatingMoves(const Board::Pos& pos) {
    if (GetChecker(pos)->IsKing()) {
        for (int i = 1; pos.first + i + 1 < 8 && pos.second + i + 1 < 8; ++i) {
            const auto* checker = GetChecker({pos.first + i, pos.second + i});

            if (checker) {
                if (checker->GetColor() != playerColor_) {
                    if (!GetChecker({pos.first + i + 1, pos.second + i + 1})) {
                        GetCell({pos.first + i + 1, pos.second + i + 1})->SetToBeat();
                    } else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }

        for (int i = 1; pos.first + i + 1 < 8 && pos.second - i - 1 >= 0; ++i) {
            const auto* checker = GetChecker({pos.first + i, pos.second - i});

            if (checker) {
                if (checker->GetColor() == playerColor_) {
                    if (!GetChecker({pos.first + i + 1, pos.second - i - 1})) {
                        GetCell({pos.first + i + 1, pos.second - i - 1})->SetToBeat();
                    } else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }

        for (int i = 1; pos.first - i - 1 >= 0 && pos.second + i + 1 < 8; ++i) {
            const auto* checker = GetChecker({pos.first - i, pos.second + i});

            if (checker) {
                if (checker->GetColor() == playerColor_) {
                    if (!GetChecker({pos.first - i - 1, pos.second + i + 1})) {
                        GetCell({pos.first - i - 1, pos.second + i + 1})->SetToBeat();
                    } else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }

        for (int i = 1; pos.first - i - 1 >= 0 && pos.second - i - 1 >= 0; ++i) {
            const auto* checker = GetChecker({pos.first - i, pos.second - i});

            if (checker) {
                if (checker->GetColor() == playerColor_) {
                    if (!GetChecker({pos.first - i - 1, pos.second - i - 1})) {
                        GetCell({pos.first - i - 1, pos.second - i - 1})->SetToBeat();
                    } else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }
    }
    else {
        if (pos.first + 2 < 8 && pos.second + 2 < 8 &&
            GetChecker({pos.first + 1, pos.second + 1}) && !GetChecker({pos.first + 2, pos.second + 2})) {
            GetCell({pos.first + 2, pos.second + 2})->SetToBeat();
        }

        if (pos.first + 2 < 8 && pos.second - 2 >= 0 &&
            GetChecker({pos.first + 1, pos.second - 1}) && !GetChecker({pos.first + 2, pos.second - 2})) {
            GetCell({pos.first + 2, pos.second - 2})->SetToBeat();
        }

        if (pos.first - 2 >= 0 && pos.second + 2 < 8 &&
            GetChecker({pos.first - 1, pos.second + 1}) && !GetChecker({pos.first - 2, pos.second + 2})) {
            GetCell({pos.first - 2, pos.second + 2})->SetToBeat();
        }

        if (pos.first - 2 >= 0 && pos.second - 2 >= 0 &&
            GetChecker({pos.first - 1, pos.second - 1}) && !GetChecker({pos.first - 2, pos.second - 2})) {
            GetCell({pos.first - 2, pos.second - 2})->SetToBeat();
        }
    }
}

void Board::ShowAllMoves(const Board::Pos& pos) {
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
        if (pos.first + 1 < 8 && pos.second + 1 < 8 && !GetChecker({pos.first + 1, pos.second + 1})) {
            GetCell({pos.first + 1, pos.second + 1})->SetToMove();
        }

        if (pos.first + 1 < 8 && pos.second - 1 >= 0 && !GetChecker({pos.first + 1, pos.second - 1})) {
            GetCell({pos.first + 1, pos.second + 1})->SetToMove();
        }

        if (pos.first - 1 >= 0 && pos.second + 1 < 8 && !GetChecker({pos.first - 1, pos.second + 1})) {
            GetCell({pos.first + 1, pos.second + 1})->SetToMove();
        }

        if (pos.first - 1 >= 0 && pos.second + 1 < 8 && !GetChecker({pos.first + 1, pos.second + 1})) {
            GetCell({pos.first + 1, pos.second + 1})->SetToMove();
        }
    }
}

void Board::ResetCells() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            GetCell({i, j})->ResetColor();
        }
    }
}

bool Board::ValidPos(const Pos& pos) {
    return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
}
