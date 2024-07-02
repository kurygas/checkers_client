#pragma once
#include <QMainWindow>
#include <QScreen>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QTcpSocket>
#include <memory>
#include <vector>
#include "socket.h"
#include "application_window.h"
#include "player_info.h"

class Lobby;

class LoginScreen : public ApplicationWindow {
public:
    LoginScreen(Socket& socket, PlayerInfo& player);
    void SetLobby(Lobby* lobby);
    void DrawWindow();
    void EraseWindow();

private:
    void Request(const std::string&);
    void OpenRegistration();
    void OpenLogin();
    void Login();
    void Register();
    void ClearBoxes();

    QLineEdit* loginBox_ = nullptr;
    QLineEdit* passwordBox_ = nullptr;
    QLabel* connectLabel_ = nullptr;
    QLabel* headerLabel_ = nullptr;
    QPushButton* swapButton_ = nullptr;
    QPushButton* activeButton_ = nullptr;

    Socket& socket_;
    PlayerInfo& player_;
    Lobby* lobby_ = nullptr;
};
