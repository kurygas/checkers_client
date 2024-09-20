#pragma once

#include <QPushButton>
#include "auth_window.h"
#include "login_window.h"

class LoginWindow;

class RegistrationWindow : public AuthWindow {
public:
    explicit RegistrationWindow(Socket* socket, PlayerInfo& playerInfo, const QString& windowTitle);

    void setLoginWindow(LoginWindow* login);

private:
    void drawWindow() override;
    void openLogin();

    void processMessage(const Query& query) override;
    void sendRegister();
    void receiveRegister(const Query& query);

    QPushButton* registerButton_ = nullptr;
    QLabel* infoLabel_ = nullptr;
    QPushButton* backButton_ = nullptr;

    LoginWindow* loginWindow_ = nullptr;
};
