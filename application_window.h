#pragma once
#include <QScreen>
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QFrame>
#include <QLabel>
#include "socket.h"
#include "player_info.h"

class ApplicationWindow : public QMainWindow {
public:
    ApplicationWindow(Socket* socket, PlayerInfo& player);

    void Open();
    void Close();

protected:
    virtual void Draw();

    virtual void ProcessMessage(const Query& message) = 0;

    static void ShowError(const QString& text);
    static void ShowInfo(const QString& text);

    Socket* socket_;
    PlayerInfo& player_;
    QVBoxLayout* layout_ = nullptr;
    QLabel* headerLabel_ = nullptr;

private:
    void ReceiveMessage();
};
