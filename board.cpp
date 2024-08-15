#include "board.h"

Board::Board(QWidget* parent, const QColor& playerColor)
: QGraphicsView(parent)
, scene_(0, 0, 400, 400)
, grid_(8, QList<Cell*>(8, nullptr))
, playerColor_(playerColor)
, myTurn_(playerColor == Color::white) {
    setScene(&scene_);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            grid_[j][i] = new Cell({j, i}, this);
            scene_.addItem(grid_[j][i]);
        }
    }
}

Cell* Board::GetCell(const QPair<uint, uint>& pos) {
     return grid_[pos.first][pos.second];
}

void Board::CellPressed(const QPair<uint, uint>& pos) {
    if (!myTurn_) {
        return;
    }

    auto* pressedCell = GetCell(pos);

    if (chosenPos_.has_value()) {

    }
    else if (pressedCell->GetChecker()->GetColor() == playerColor_) {
        chosenPos_ = pos;
        pressedCell->SetChosen(true);
    }
}
