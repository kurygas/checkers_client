#pragma once
#include <QMainWindow>
#include <QLabel>
#include "socket.h"
#include "application_window.h"
#include "player_info.h"

class LoginScreen;

class Lobby : public ApplicationWindow {
public:
    Lobby(Socket& socket, PlayerInfo& player, LoginScreen* loginScreen);
    void DrawWindow();
    void EraseWindow();

private:
    QLabel* nicknameLabel_ = nullptr;

    Socket& socket_;
    PlayerInfo& player_;
    LoginScreen* loginScreen_;
};
