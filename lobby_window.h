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

using namespace std::chrono_literals;

class LobbyWindow : public ApplicationWindow {
public:
    LobbyWindow(Socket* socket, PlayerInfo& player);
    void SetLoginWindow(ApplicationWindow* loginWindow);

private:
    void Draw() override;
    void OpenLogin();
    void SearchLabelTimeout();

    void ProcessMessage(const Query& query) override;
    void SendFindGame();
    void ReceiveStartGame(const Query& query);
    void SendCancelSearching();
    void ReceiveCancelSearching();

    QLabel* nicknameLabel_ = nullptr;
    QLabel* ratingLabel_ = nullptr;
    QPushButton* changeNicknameButton_ = nullptr;
    QPushButton* changePasswordButton_ = nullptr;
    QPushButton* logOutButton_ = nullptr;
    QPushButton* searchButton_ = nullptr;
    QPushButton* cancelButton_ = nullptr;
    QLabel* infoLabel_ = nullptr;
    QTimer* searchingTimer_ = nullptr;
    uint timeInSearch_ = 0;

    ApplicationWindow* loginWindow_ = nullptr;
};
