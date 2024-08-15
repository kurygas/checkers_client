#pragma once
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include "socket.h"
#include "player_info.h"

class ApplicationWindow : public QMainWindow {
public:
    ApplicationWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle);

    void Open();
    void Close();

protected:
    virtual void Draw();

    virtual void ProcessMessage(const Query& message) = 0;

    static void ShowError(const QString& text);
    static void ShowInfo(const QString& text);
    static bool CheckNickname(const QString& nickname);
    static bool CheckPassword(const QString& password);

    Socket* socket_;
    PlayerInfo& player_;
    QVBoxLayout* layout_ = nullptr;

private:
    void ReceiveMessage();
};
