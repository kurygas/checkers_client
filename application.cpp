#include "application.h"

Application::Application(int argc, char **argv)
: QApplication(argc, argv)
, loginScreen_(socket_, player_)
, lobby_(socket_, player_, &loginScreen_) {
    socket_.ConnectToServer();
    loginScreen_.SetLobby(&lobby_);
    connect(this, &QApplication::aboutToQuit, &socket_, &Socket::PrepareForClose);
    loginScreen_.DrawWindow();
}
