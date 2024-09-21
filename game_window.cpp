#include "game_window.h"

GameWindow::GameWindow(Socket* socket, PlayerInfo& playerInfo, const QString& windowTitle)
: ApplicationWindow(socket, playerInfo, windowTitle) {}

void GameWindow::setLobbyWindow(LobbyWindow* lobbyWindow) {
    lobbyWindow_ = lobbyWindow;
}

void GameWindow::drawWindow() {
    ApplicationWindow::drawWindow();

    myTurn_ = playerInfo_.color == Color::white;

    enemyNicknameLabel_ = new QLabel("Your enemy: " + playerInfo_.enemyNickname, centralWidget());
    layout_->addWidget(enemyNicknameLabel_);

    enemyRatingLabel_ = new QLabel("Enemy's rating: " + QString::number(playerInfo_.enemyRating), centralWidget());
    layout_->addWidget(enemyRatingLabel_);

    colorLabel_ = new QLabel("Your color: " + QString(myTurn_ ? "white" : "black"), centralWidget());
    layout_->addWidget(colorLabel_);

    turnLabel_ = new QLabel(myTurn_ ? "Your turn" : "Enemy turn", centralWidget());
    layout_->addWidget(turnLabel_);

    board_ = new Board(centralWidget(), playerInfo_.color, this);
    layout_->addWidget(board_);
}

void GameWindow::processMessage(const Query& query) {
    const auto id = query.getType();

    if (id == QueryId::Move) {
        receiveMove(query);
    }
    else if (id == QueryId::EnemyDisconnected) {
        receiveDisconnect();
    }
    else if (id == QueryId::Lose) {
        receiveMatchResult();
    }
}

bool GameWindow::isMyTurn() const {
    return myTurn_;
}

void GameWindow::sendMoves(const QList<QPair<Pos, Pos>>& moves) {
    myTurn_ = false;
    turnLabel_->setText("Enemy turn");
    Query query(QueryId::Move);
    query.pushShort(static_cast<int>(moves.size()));

    for (const auto& move : moves) {
        query.pushShort( 7 - move.first.first);
        query.pushShort(7 - move.first.second);
        query.pushShort(7 - move.second.first);
        query.pushShort(7 - move.second.second);
    }

    socket_->writeMessage(query);
}

void GameWindow::receiveMove(const Query& query) {
    myTurn_ = true;
    turnLabel_->setText("Your turn");

    for (auto i = 0; i < query.getInt(0) * 4; i += 4) {
        const Pos from(query.getInt(i + 1), query.getInt(i + 2));
        const Pos to(query.getInt(i + 3), query.getInt(i + 4));
        board_->moveChecker(from, to);
    }
}

void GameWindow::sendMatchResult() {
    socket_->writeMessage(Query(QueryId::Win));
    showInfo("You have won your enemy and earned 50 points");
    playerInfo_.rating += 50;
    changeWindow(lobbyWindow_);
}

void GameWindow::receiveDisconnect() {
    showInfo("Your enemy has disconnected. You have earned 50 points");
    playerInfo_.rating += 50;
    changeWindow(lobbyWindow_);
}

void GameWindow::receiveMatchResult() {
    showInfo("You have lost 50 points after this match");
    playerInfo_.rating -= std::min(50, playerInfo_.rating);
    changeWindow(lobbyWindow_);
}
