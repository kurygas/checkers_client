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

class LoginScreen : public QMainWindow {
public:
    LoginScreen();

private:
    void Request(const std::string&);
    void OpenRegistration();
    void OpenLogin();
    void Login();
    void Register();
    void ClearBoxes();
    void OpenLobby();
    void SetLobby(QMainWindow* lobby);

    QHostAddress serverAddress_;
    int serverPort_ = 8080;
    QTcpSocket* socket_;

    int screenWidth_;
    QLineEdit* loginBox_;
    QLineEdit* passwordBox_;
    QLabel* connectLabel_;
    QLabel* headerLabel_;
    QPushButton* swapButton_;
    QPushButton* activeButton_;

    QMainWindow* lobby_ = nullptr;
};