#pragma once
#include <QLineEdit>
#include "application_window.h"

class AuthWindow : public ApplicationWindow {
public:
    AuthWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle);

protected:
    void Draw() override;
    bool CheckBoxes() const;

    QLineEdit* nicknameBox_ = nullptr;
    QLineEdit* passwordBox_ = nullptr;
};