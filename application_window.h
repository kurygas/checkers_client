#pragma once
#include <QScreen>
#include <QApplication>
#include <QMainWindow>
#include <QLayoutItem>
#include "socket.h"
#include "player_info.h"

class ApplicationWindow : public QMainWindow {
public:
    ApplicationWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle);

    void Open();
    void Close();

protected:
    virtual void Draw() = 0;

    void ReceiveMessage();
    virtual void ProcessMessage(const Query& message) = 0;

    bool isActive_ = false;
    int screenWidth_;
    int screenHeight_;
    Socket* socket_;
    PlayerInfo& player_;
};
