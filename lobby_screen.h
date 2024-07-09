#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QTimer>
#include "application_window.h"

using namespace std::chrono_literals;

class LobbyScreen : public ApplicationWindow {
public:
    LobbyScreen(Socket* socket, PlayerInfo& player, ApplicationWindow* loginScreen);
    void SetGameScreen(ApplicationWindow* gameScreen);

private:
    void Draw() override;
    void EnableRefreshButton();

    void ProcessMessage(const QList<QString>& message) override;
    void SendRoomList();
    void SendJoinToRoom();
    void SendCreateRoom();
    void ReceiveRoomList(const QList<QString>& message);
    void ReceiveJoinToRoom(const QList<QString>& message);
    void ReceiveCreateRoom(const QList<QString>& message);

    QLabel* nicknameLabel_ = nullptr;
    QLabel* ratingLabel_ = nullptr;
    QPushButton* createButton_ = nullptr;
    QPushButton* refreshButton_ = nullptr;
    QDialogButtonBox* buttonBox_ = nullptr;
    QTimer* refreshTimer_ = nullptr;

    ApplicationWindow* loginScreen_;
    ApplicationWindow* gameScreen_ = nullptr;
};
