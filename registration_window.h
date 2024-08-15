#pragma once
#include <QPushButton>
#include "auth_window.h"
#include "login_window.h"

class LoginWindow;

class RegistrationWindow : public AuthWindow {
public:
    explicit RegistrationWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle);
    void SetLoginWindow(LoginWindow* login);

private:
    void Draw() override;
    void OpenLogin();

    void ProcessMessage(const Query& query) override;
    void SendRegister();
    void ReceiveRegister(const Query& query);

    QPushButton* registerButton_ = nullptr;
    QLabel* infoLabel_ = nullptr;
    QPushButton* backButton_ = nullptr;

    LoginWindow* loginWindow_ = nullptr;
};
