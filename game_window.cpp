#include "game_window.h"

GameWindow::GameWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle)
: ApplicationWindow(socket, player, windowTitle) {}

void GameWindow::SetLobbyWindow(LobbyWindow* lobbyWindow) {
    lobbyWindow_ = lobbyWindow;
}

void GameWindow::Draw() {
    ApplicationWindow::Draw();

    enemyNicknameLabel_ = new QLabel("Your enemy: " + player_.enemyNickname, centralWidget());
    layout_->addWidget(enemyNicknameLabel_);

    enemyRatingLabel_ = new QLabel("Enemy's rating: " + QString::number(player_.enemyRating), centralWidget());
    layout_->addWidget(enemyRatingLabel_);

    board_ = new Board(centralWidget(), player_.playerColor);
    layout_->addWidget(board_);
}

void GameWindow::ProcessMessage(const Query& query) {

}
