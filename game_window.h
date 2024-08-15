#pragma once
#include <QGridLayout>
#include <QMouseEvent>
#include "application_window.h"
#include "board.h"
#include "lobby_window.h"

class LobbyWindow;

class GameWindow : public ApplicationWindow {
public:
    GameWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle);
    void SetLobbyWindow(LobbyWindow* lobbyWindow);

private:
    void Draw() override;

    void ProcessMessage(const Query& query) override;

    QLabel* enemyNicknameLabel_ = nullptr;
    QLabel* enemyRatingLabel_ = nullptr;
    Board* board_ = nullptr;

    LobbyWindow* lobbyWindow_ = nullptr;
};