#pragma once
#include <QMainWindow>
#include <QScreen>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include "auth_window.h"

class LoginWindow : public AuthWindow {
public:
    LoginWindow(Socket* socket, PlayerInfo& player);
    void SetLobbyWindow(ApplicationWindow* lobby);
    void SetRegisterWindow(ApplicationWindow* reg);

private:
    void Draw() override;
    void OpenRegistration();

    void ProcessMessage(const Query& query) override;
    void SendLogin();
    void ReceiveLogin(const Query& query);

    QPushButton* loginButton_ = nullptr;
    QLabel* infoLabel_ = nullptr;
    QPushButton* registerButton_ = nullptr;

    ApplicationWindow* lobbyWindow_ = nullptr;
    ApplicationWindow* registrationWindow_ = nullptr;
};
