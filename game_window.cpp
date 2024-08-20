#include "game_window.h"

GameWindow::GameWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle)
: ApplicationWindow(socket, player, windowTitle) {}

void GameWindow::SetLobbyWindow(LobbyWindow* lobbyWindow) {
    lobbyWindow_ = lobbyWindow;
}

void GameWindow::Draw() {
    ApplicationWindow::Draw();

    myTurn_ = player_.color == Color::white;

    enemyNicknameLabel_ = new QLabel("Your enemy: " + player_.enemyNickname, centralWidget());
    layout_->addWidget(enemyNicknameLabel_);

    enemyRatingLabel_ = new QLabel("Enemy's rating: " + QString::number(player_.enemyRating), centralWidget());
    layout_->addWidget(enemyRatingLabel_);

    colorLabel_ = new QLabel("Your color: " + QString(myTurn_ ? "white" : "black"), centralWidget());
    layout_->addWidget(colorLabel_);

    turnLabel_ = new QLabel(myTurn_ ? "Your turn" : "Enemy turn", centralWidget());
    layout_->addWidget(turnLabel_);

    board_ = new Board(centralWidget(), player_.color, this);
    layout_->addWidget(board_);
}

void GameWindow::ProcessMessage(const Query& query) {
    const auto id = query.Type();

    if (id == QueryId::Move) {
        ReceiveMove(query);
    }
    else if (id == QueryId::EnemyDisconnected) {
        ReceiveDisconnect();
    }
}

bool GameWindow::IsMyTurn() const {
    return myTurn_;
}

void GameWindow::SendMoves(const QList<QPair<Pos, Pos>>& moves) {
    myTurn_ = false;
    turnLabel_->setText("Enemy turn");
    Query query(QueryId::Move);
    query.PushInt(moves.size());

    for (const auto& move : moves) {
        query.PushInt(move.first.first);
        query.PushInt(move.first.second);
        query.PushInt(move.second.first);
        query.PushInt(move.second.second);
    }

    socket_->Write(query);
}

void GameWindow::ReceiveMove(const Query& query) {
    myTurn_ = true;
    turnLabel_->setText("Your turn");

    for (uint i = 0; i < query.GetInt(0); ++i) {
        const Pos from(query.GetInt(i + 1), query.GetInt(i + 2));
        const Pos to(query.GetInt(i + 3), query.GetInt(i + 4));
        board_->MoveChecker(from, to);

        if (abs(from.first - to.first) > 1) {
            board_->RemoveChecker(Board::GetMiddlePos(from, to));
        }
    }
}

void GameWindow::SendMatchResult() {
    socket_->Write(Query(QueryId::Win));
}
