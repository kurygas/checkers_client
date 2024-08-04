#pragma once
#include <QLineEdit>
#include <QPushButton>
#include "auth_window.h"

class RegistrationWindow : public AuthWindow {
public:
    explicit RegistrationWindow(Socket* socket, PlayerInfo& player);
    void SetLoginWindow(ApplicationWindow* login);

private:
    void Draw() override;
    void OpenLogin();

    void ProcessMessage(const Query& query) override;
    void SendRegister();
    void ReceiveRegister(const Query& query);

    QPushButton* registerButton_ = nullptr;
    QLabel* infoLabel_ = nullptr;
    QPushButton* backButton_ = nullptr;

    ApplicationWindow* loginWindow_ = nullptr;
};
