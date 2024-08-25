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
        const auto& checkerPos = chosenPos_.value();
        MoveChecker(checkerPos, pos);
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

        if (GetChecker(pos) && GetChecker(pos)->GetColor() == playerColor_) {
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
        for (const auto& move : moves_) {
            for (Pos to = pos + move; IsValid(to); to += move) {
                if (!GetChecker(to)) {
                    GetCell(to)->SetToMove();
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
            if (IsValid(to) && !GetChecker(to) && (move.second == 1 && playerColor_ == Color::white ||
            move.second == -1 && playerColor_ == Color::black)) {
                GetCell(to)->SetToMove();
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

QList<Pos> Board::PosToBeat(const Pos& pos) {
    QList<Pos> result;

    if (GetChecker(pos)->IsKing()) {
        for (const auto& move : moves_) {
            bool metChecker = false;

            for (Pos to = pos + move; IsValid(to); to += move) {
                const auto* checker = GetChecker(to);

                if (checker) {
                    if (metChecker || checker->GetColor() == playerColor_) {
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

            if (IsValid(to + move)) {
                const auto* checker = GetChecker(to);

                if (checker && !GetChecker(to + move) && checker->GetColor() != playerColor_) {
                    result.emplace_back(to + move);
                }
            }
        }
    }

    return result;
}

void Board::MoveChecker(const Pos& from, const Pos& to) {
    GetChecker(from)->ChangeCell(GetCell(to));
    GetCell(to)->SetChecker(GetChecker(from));
    GetCell(from)->ReleaseChecker();
    const auto& color = GetChecker(to)->GetColor();

    if (to.second == 7 && color == Color::white || to.second == 0 && color == Color::black) {
        GetChecker(to)->MakeKing();
    }

    if (GetChecker(GetBeatenPos(from, to))) {
        RemoveChecker(GetBeatenPos(from, to));
    }
}

Pos Board::GetBeatenPos(const Pos& pos1, const Pos& pos2) {
    auto diff = pos1 - pos2;
    diff.Normalize();

    for (Pos p = pos2 + diff; p != pos1; p += diff) {
        if (GetChecker(p)) {
            return p;
        }
    }

    return {0, 0};
}

void Board::RemoveChecker(const Pos& pos) {
    if (GetChecker(pos)->GetColor() != playerColor_) {
        --enemyCheckerCount;
    }

    GetCell(pos)->RemoveChecker();
}

bool Board::IsValid(const Pos& pos) {
    return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
}
