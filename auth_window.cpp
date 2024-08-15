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
    return CheckNickname(nicknameBox_->text()) && CheckPassword(passwordBox_->text());
}

AuthWindow::AuthWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle)
: ApplicationWindow(socket, player, windowTitle) {}
