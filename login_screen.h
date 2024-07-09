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
    LoginScreen(Socket* socket, PlayerInfo& player);
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

    void ProcessMessage(const QList<QString>& message) override;
    void SendLogin();
    void SendRegister();
    void ReceiveLogin(const QList<QString>& message);
    void ReceiveRegister(const QList<QString>& message);

    QLineEdit* loginBox_ = nullptr;
    QLineEdit* passwordBox_ = nullptr;
    QLabel* infoLabel_ = nullptr;
    QLabel* headerLabel_ = nullptr;
    QPushButton* swapButton_ = nullptr;
    QPushButton* activeButton_ = nullptr;

    ApplicationWindow* lobby_ = nullptr;
};
