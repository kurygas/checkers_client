#pragma once
#include <QGridLayout>
#include <QMouseEvent>
#include "application_window.h"
#include "board.h"
#include "lobby_window.h"

class LobbyWindow;
class Board;

class GameWindow : public ApplicationWindow {
public:
    using Pos = QPair<int, int>;

    GameWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle);
    void SetLobbyWindow(LobbyWindow* lobbyWindow);
    bool IsMyTurn() const;

    void SendMoves(const QList<QPair<Pos, Pos>>& moves);
    void SendMatchResult();

private:
    void Draw() override;

    void ProcessMessage(const Query& query) override;
    void ReceiveMove(const Query& query);
    void ReceiveDisconnect();

    QLabel* enemyNicknameLabel_ = nullptr;
    QLabel* enemyRatingLabel_ = nullptr;
    QLabel* colorLabel_ = nullptr;
    QLabel* turnLabel_ = nullptr;
    Board* board_ = nullptr;
    bool myTurn_ = false;

    LobbyWindow* lobbyWindow_ = nullptr;
};
