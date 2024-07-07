#pragma once
#include <QMainWindow>
#include <QLabel>
#include "application_window.h"

class Lobby : public ApplicationWindow {
public:
    Lobby(Socket& socket, PlayerInfo& player, ApplicationWindow* loginScreen);
    void DrawWindow() override;
    void EraseWindow() override;

private:
    QLabel* nicknameLabel_ = nullptr;

    ApplicationWindow* loginScreen_;
};
