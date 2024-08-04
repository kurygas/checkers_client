#include "auth_window.h"

void AuthWindow::Draw() {
    ApplicationWindow::Draw();

    nicknameBox_ = new QLineEdit(centralWidget());
    nicknameBox_->setPlaceholderText("Type your nickname");
    layout_->addWidget(nicknameBox_);

    passwordBox_ = new QLineEdit(centralWidget());
    passwordBox_->setPlaceholderText("Type your password");
    passwordBox_->setEchoMode(QLineEdit::Password);
    layout_->addWidget(passwordBox_);
}

bool AuthWindow::CheckBoxes() const {
    const auto& nickname = nicknameBox_->text();
    const auto& password = passwordBox_->text();

    if (nickname.size() < 3) {
        ShowError("Nickname must contain at least 3 characters");
        return false;
    }

    if (password.size() < 6) {
        ShowError("Password must contain at least 6 characters");
        return false;
    }

    return true;
}

AuthWindow::AuthWindow(Socket* socket, PlayerInfo& player)
: ApplicationWindow(socket, player) {}
