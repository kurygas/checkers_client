#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>

#include "socket.h"
#include "player_info.h"

class ApplicationWindow : public QMainWindow {
public:
    ApplicationWindow(Socket* socket, PlayerInfo& playerInfo, const QString& windowTitle);

    void openWindow();
    void closeWindow();

    ~ApplicationWindow() override = 0;

protected:
    virtual void drawWindow();
    void changeWindow(ApplicationWindow* newWindow);

    virtual void processMessage(const Query& message) = 0;

    static void showError(const QString& text);
    static void showInfo(const QString& text);
    static bool checkNickname(const QString& nickname);
    static bool checkPassword(const QString& password);

    Socket* socket_;
    PlayerInfo& playerInfo_;
    QVBoxLayout* layout_ = nullptr;

private:
    void receiveMessage();
};
