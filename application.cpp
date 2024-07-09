#include "application.h"

Application::Application(int argc, char **argv)
: QApplication(argc, argv)
, socket_(new Socket(this))
, loginScreen_(socket_, player_)
, lobby_(socket_, player_, &loginScreen_) {
    socket_->ConnectToServer();
    loginScreen_.SetLobbyScreen(&lobby_);
    connect(this, &QApplication::aboutToQuit, socket_, &Socket::PrepareForClose);
    loginScreen_.Open();
}