#include "application.h"

Application::Application(int argc, char **argv)
: QApplication(argc, argv)
, socket_(new Socket(this))
, loginWindow_(socket_, player_, "Authorization")
, lobbyWindow_(socket_, player_, "Checkers Online")
, registrationWindow_(socket_, player_, "Registration")
, gameWindow_(socket_, player_, "Game") {
    socket_->ConnectToServer();
    loginWindow_.SetLobbyWindow(&lobbyWindow_);
    loginWindow_.SetRegisterWindow(&registrationWindow_);
    registrationWindow_.SetLoginWindow(&loginWindow_);
    lobbyWindow_.SetLoginWindow(&loginWindow_);
    lobbyWindow_.SetGameWindow(&gameWindow_);
    gameWindow_.SetLobbyWindow(&lobbyWindow_);
    connect(this, &QApplication::aboutToQuit, socket_, &Socket::PrepareForClose);
    loginWindow_.Open();
}
