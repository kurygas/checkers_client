#pragma once
#include <QApplication>
#include "socket.h"
#include "login_window.h"
#include "lobby_window.h"
#include "player_info.h"
#include "registration_window.h"

class Application : public QApplication {
public:
    Application(int argc, char* argv[]);

private:
    PlayerInfo player_;
    Socket* socket_;
    LoginWindow loginWindow_;
    LobbyWindow lobbyWindow_;
    RegistrationWindow registrationWindow_;
};