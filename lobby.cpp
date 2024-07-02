#include "lobby.h"

Lobby::Lobby(Socket& socket, PlayerInfo& player, LoginScreen* loginScreen)
: socket_(socket)
, player_(player)
, loginScreen_(loginScreen) {}

void Lobby::DrawWindow() {
    nicknameLabel_ = new QLabel(this);
    nicknameLabel_->setGeometry(0, 0, screenWidth_, 250);
    nicknameLabel_->setAlignment(Qt::AlignCenter);

    show();
}

void Lobby::EraseWindow() {
    delete nicknameLabel_;

    hide();
}
