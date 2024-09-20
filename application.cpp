#include "application.h"

Application::Application(int argc, char **argv)
: QApplication(argc, argv)
, socket_(new Socket(this))
, loginWindow_(socket_, playerInfo_, "Authorization")
, lobbyWindow_(socket_, playerInfo_, "Checkers Online")
, registrationWindow_(socket_, playerInfo_, "Registration")
, gameWindow_(socket_, playerInfo_, "Game") {
    socket_->connectToServer();
    loginWindow_.setLobbyWindow(&lobbyWindow_);
    loginWindow_.setRegisterWindow(&registrationWindow_);
    registrationWindow_.setLoginWindow(&loginWindow_);
    lobbyWindow_.setLoginWindow(&loginWindow_);
    lobbyWindow_.setGameWindow(&gameWindow_);
    gameWindow_.setLobbyWindow(&lobbyWindow_);
    connect(this, &QApplication::aboutToQuit, socket_, &Socket::prepareForClose);
    loginWindow_.openWindow();
}
