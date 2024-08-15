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
    void SetLobbyWindow(LobbyWindow* lobby);
    void SetRegisterWindow(RegistrationWindow* reg);

private:
    void Draw() override;
    void OpenRegistration();

    void ProcessMessage(const Query& query) override;
    void SendLogin();
    void ReceiveLogin(const Query& query);

    QPushButton* loginButton_ = nullptr;
    QLabel* infoLabel_ = nullptr;
    QPushButton* registerButton_ = nullptr;


    LobbyWindow* lobbyWindow_ = nullptr;
    RegistrationWindow* registrationWindow_ = nullptr;
};
