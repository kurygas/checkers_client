#pragma once
#include <QApplication>
#include "socket.h"
#include "login_screen.h"
#include "lobby_screen.h"
#include "player_info.h"

class Application : public QApplication {
public:
    Application(int argc, char* argv[]);

private:
    PlayerInfo player_;
    Socket* socket_;
    LoginScreen loginScreen_;
    LobbyScreen lobby_;
};
