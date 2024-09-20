#pragma once

#include <QPushButton>

#include "auth_window.h"
#include "registration_window.h"
#include "lobby_window.h"

class RegistrationWindow;
class LobbyWindow;

class LoginWindow : public AuthWindow {
public:
    LoginWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle);

    void setLobbyWindow(LobbyWindow* lobbyWindow);
    void setRegisterWindow(RegistrationWindow* registrationWindow);

private:
    void drawWindow() override;
    void openRegistration();

    void processMessage(const Query& query) override;
    void sendLogin();
    void receiveLogin(const Query& query);

    QPushButton* loginButton_ = nullptr;
    QLabel* infoLabel_ = nullptr;
    QPushButton* registerButton_ = nullptr;

    LobbyWindow* lobbyWindow_ = nullptr;
    RegistrationWindow* registrationWindow_ = nullptr;
};
