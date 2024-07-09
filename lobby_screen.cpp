#include "lobby_screen.h"

LobbyScreen::LobbyScreen(Socket* socket, PlayerInfo& player, ApplicationWindow* loginScreen)
: ApplicationWindow(socket, player)
, loginScreen_(loginScreen) {}

void LobbyScreen::Draw() {
    nicknameLabel_ = new QLabel(this);
    nicknameLabel_->setGeometry(10, 10, screenWidth_ / 2, 50);
    nicknameLabel_->setFont(QFont("Arial", 25));
    nicknameLabel_->setText(player_.GetNickname());

    ratingLabel_ = new QLabel(this);
    ratingLabel_->setGeometry(10, 70, screenWidth_ / 2, 50);
    ratingLabel_->setFont(QFont("Arial", 25));
    ratingLabel_->setText("Rating " + QString::number(player_.GetRating()));
}

void LobbyScreen::SetGameScreen(ApplicationWindow* gameScreen) {
    gameScreen_ = gameScreen;
}

void LobbyScreen::ProcessMessage(const QList<QString>& message) {

}
