#pragma once
#include <QPushButton>
#include <QTimer>
#include <QInputDialog>
#include "application_window.h"
#include "login_window.h"
#include "game_window.h"
#include "color.h"

using namespace std::chrono_literals;
class LoginWindow;
class GameWindow;

class LobbyWindow : public ApplicationWindow {
public:
    LobbyWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle);
    void SetLoginWindow(LoginWindow* loginWindow);
    void SetGameWindow(GameWindow* gameWindow);

private:
    void Draw() override;
    void SearchLabelTimeout();
    void EnableButtons(bool state);

    void ProcessMessage(const Query& query) override;
    void SendFindGame();
    void ReceiveStartGame(const Query& query);
    void SendCancelSearching();
    void ReceiveCancelSearching();
    void SendLogout();
    void SendChangeNickname();
    void ReceiveChangeNickname(const Query& query);
    void SendChangePassword();
    void ReceiveChangePassword(const Query& query);

    QLabel* nicknameLabel_ = nullptr;
    QLabel* ratingLabel_ = nullptr;
    QPushButton* changeNicknameButton_ = nullptr;
    QPushButton* changePasswordButton_ = nullptr;
    QPushButton* logoutButton_ = nullptr;
    QPushButton* searchButton_ = nullptr;
    QPushButton* cancelButton_ = nullptr;
    QLabel* infoLabel_ = nullptr;
    QTimer* searchingTimer_ = nullptr;
    uint timeInSearch_ = 0;
    bool inSearch_ = false;

    LoginWindow* loginWindow_ = nullptr;
    GameWindow* gameWindow_ = nullptr;
};
