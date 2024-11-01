#pragma once

#include <QGridLayout>
#include <QMouseEvent>

#include "application_window.h"
#include "board.h"
#include "lobby_window.h"
#include "pos.h"

class LobbyWindow;
class Board;

class GameWindow : public ApplicationWindow {
public:
    GameWindow(Socket* socket, PlayerInfo& playerInfo, const QString& windowTitle);

    void setLobbyWindow(LobbyWindow* lobbyWindow);
    bool isMyTurn() const;

    void sendMoves(const QList<QPair<Pos, Pos>>& moves);
    void sendMatchResult();

    ~GameWindow() override = default;

private:
    void drawWindow() override;

    void processMessage(const Query& query) override;
    void receiveMove(const Query& query);
    void receiveDisconnect();
    void receiveMatchResult();

    QLabel* enemyNicknameLabel_ = nullptr;
    QLabel* enemyRatingLabel_ = nullptr;
    QLabel* colorLabel_ = nullptr;
    QLabel* turnLabel_ = nullptr;
    Board* board_ = nullptr;
    bool myTurn_ = false;

    LobbyWindow* lobbyWindow_ = nullptr;
};
