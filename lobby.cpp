#include "lobby.h"

Lobby::Lobby(Socket& socket, PlayerInfo& player, ApplicationWindow* loginScreen)
: ApplicationWindow(socket, player)
, loginScreen_(loginScreen) {}

void Lobby::DrawWindow() {
    nicknameLabel_ = new QLabel(this);
    nicknameLabel_->setGeometry(0, 0, screenWidth_, 250);
    nicknameLabel_->setAlignment(Qt::AlignCenter);
    nicknameLabel_->setText(player_.GetNickname());

    show();
}

void Lobby::EraseWindow() {
    delete nicknameLabel_;

    hide();
}
