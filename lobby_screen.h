#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <QVBoxLayout>
#include <QInputDialog>
#include "application_window.h"
#include "room_button.h"
#include "create_room_window.h"

using namespace std::chrono_literals;

class LobbyScreen : public ApplicationWindow {
public:
    LobbyScreen(const QString& windowTitle, Socket* socket, PlayerInfo& player, ApplicationWindow* loginScreen);
    void SetGameScreen(ApplicationWindow* gameScreen);

private:
    void Draw() override;
    void EnableRefreshButton();
    void AddLine();
    void SetReadyToPlay(bool ready);
    void EnableChangeNickname();
    void EnableChangePassword();

    void ProcessMessage(const Query& query) override;
    void SendRoomList();
    void SendJoinToRoom();
    void SendCreateRoom();
    void SendDelete();
    void SendAccept();
    void SendChangePassword();
    void SendChangeNickname();
    void ReceiveRoomList(const Query& query);
    void ReceiveJoinToRoom(const Query& query);
    void ReceiveChangeNickname(const Query& query);
    void ReceiveChangePassword(const Query& query);
    void ReceiveAcceptResult(const Query& query);
    void ReceiveAccept(const Query& query);

    QVBoxLayout* leftLayout_ = nullptr;
    QWidget* leftContainer_ = nullptr;
    QLabel* nicknameLabel_ = nullptr;
    QLabel* ratingLabel_ = nullptr;
    QPushButton* createButton_ = nullptr;
    QPushButton* refreshButton_ = nullptr;
    QWidget* buttonContainer_ = nullptr;
    QVBoxLayout* buttonLayout_ = nullptr;
    QTimer* refreshTimer_ = nullptr;
    QLabel* infoLabel_ = nullptr;
    QPushButton* cancelButton_ = nullptr;
    QLabel* timerLabel_ = nullptr;
    QPushButton* changePasswordButton_ = nullptr;
    QPushButton* changeNicknameButton_ = nullptr;
    QTimer* changeNicknameTimer_ = nullptr;
    QTimer* changePasswordTimer_ = nullptr;

    bool waitList_ = false;
    QString roomToPlay_;
    QString newNickname_;
    QString newPassword_;

    ApplicationWindow* loginScreen_;
    ApplicationWindow* gameScreen_ = nullptr;
};
