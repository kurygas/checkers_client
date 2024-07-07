#pragma once
#include <QScreen>
#include <QApplication>
#include <QMainWindow>
#include "socket.h"
#include "player_info.h"

class ApplicationWindow : public QMainWindow {
public:
    ApplicationWindow(Socket& socket, PlayerInfo& player);
    virtual void DrawWindow() = 0;
    virtual void EraseWindow() = 0;

protected:
    int screenWidth_;
    int screenHeight_;
    Socket& socket_;
    PlayerInfo& player_;
};