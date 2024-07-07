#pragma once
#include <QApplication>
#include "socket.h"
#include "login_screen.h"
#include "lobby.h"
#include "player_info.h"

class Application : public QApplication {
public:
    Application(int argc, char* argv[]);

private:
    Socket socket_;
    PlayerInfo player_;
    LoginScreen loginScreen_;
    Lobby lobby_;
};