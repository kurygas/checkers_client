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

    void setLoginWindow(LoginWindow* loginWindow);
    void setGameWindow(GameWindow* gameWindow);

    ~LobbyWindow() override = default;

private:
    void drawWindow() override;
    void searchLabelTimeout();
    void enableButtons(bool state);

    void processMessage(const Query& query) override;
    void sendFindGame();
    void receiveStartGame(const Query& query);
    void sendCancelSearching();
    void receiveCancelSearching();
    void sendLogout();
    void sendChangeNickname();
    void receiveChangeNickname(const Query& query);
    void sendChangePassword();
    void receiveChangePassword(const Query& query);

    QLabel* nicknameLabel_ = nullptr;
    QLabel* ratingLabel_ = nullptr;
    QPushButton* changeNicknameButton_ = nullptr;
    QPushButton* changePasswordButton_ = nullptr;
    QPushButton* logoutButton_ = nullptr;
    QPushButton* searchButton_ = nullptr;
    QPushButton* cancelButton_ = nullptr;
    QLabel* infoLabel_ = nullptr;
    QTimer* searchingTimer_ = nullptr;
    int timeInSearch_ = 0;
    bool inSearch_ = false;

    LoginWindow* loginWindow_ = nullptr;
    GameWindow* gameWindow_ = nullptr;
};
