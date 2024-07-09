#pragma once
#include <QMainWindow>
#include <QLabel>
#include "application_window.h"

class LobbyScreen : public ApplicationWindow {
public:
    LobbyScreen(Socket* socket, PlayerInfo& player, ApplicationWindow* loginScreen);
    void SetGameScreen(ApplicationWindow* gameScreen);

private:
    void Draw() override;

    void ProcessMessage(const QList<QString>& message) override;

    QLabel* nicknameLabel_ = nullptr;
    QLabel* ratingLabel_ = nullptr;

    ApplicationWindow* loginScreen_;
    ApplicationWindow* gameScreen_ = nullptr;
};
