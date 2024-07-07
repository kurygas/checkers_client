#pragma once
#include <QMainWindow>
#include <QScreen>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include "application_window.h"

class LoginScreen : public ApplicationWindow {
public:
    LoginScreen(Socket& socket, PlayerInfo& player);
    void SetLobby(ApplicationWindow* lobby);
    void DrawWindow() override;
    void EraseWindow() override;

private:
    void Request(const QString&);
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

    ApplicationWindow* lobby_ = nullptr;
};
