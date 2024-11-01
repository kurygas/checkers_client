#pragma once

#include <QLineEdit>

#include "application_window.h"

class AuthWindow : public ApplicationWindow {
public:
    AuthWindow(Socket* socket, PlayerInfo& playerInfo, const QString& windowTitle);

    ~AuthWindow() override = default;

protected:
    void drawWindow() override;

    bool checkBoxes() const;

    QLineEdit* nicknameBox_ = nullptr;
    QLineEdit* passwordBox_ = nullptr;
};
