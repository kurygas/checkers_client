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
    LoginScreen(const QString& windowTitle, Socket* socket, PlayerInfo& player);
    void SetLobbyScreen(ApplicationWindow* lobby);

private:
    void Draw() override;
    void OpenRegistration();
    void OpenLogin();
    void ClearBoxes();
    void ShowError();
    void ShowWaitMessage();
    void ShowSuccess();
    bool CheckBoxesInfo();
    void EnableButtons();

    void ProcessMessage(const Query& query) override;
    void SendLogin();
    void SendRegister();
    void ReceiveLogin(const Query& query);
    void ReceiveRegister(const Query& query);

    QLineEdit* loginBox_ = nullptr;
    QLineEdit* passwordBox_ = nullptr;
    QLabel* infoLabel_ = nullptr;
    QLabel* headerLabel_ = nullptr;
    QPushButton* swapButton_ = nullptr;
    QPushButton* activeButton_ = nullptr;

    ApplicationWindow* lobby_ = nullptr;
};
