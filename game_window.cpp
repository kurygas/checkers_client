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

    colorLabel_ = new QLabel("Your color: " + QString(player_.color == Color::white ? "white" : "black"));
    layout_->addWidget(colorLabel_);

    board_ = new Board(centralWidget(), player_.color, this);
    layout_->addWidget(board_);
}

void GameWindow::ProcessMessage(const Query& query) {

}

bool GameWindow::IsMyTurn() const {
    return myTurn_;
}
