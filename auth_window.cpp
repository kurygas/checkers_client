#include "auth_window.h"

void AuthWindow::drawWindow() {
    ApplicationWindow::drawWindow();

    nicknameBox_ = new QLineEdit(centralWidget());
    nicknameBox_->setPlaceholderText("Type your nickname");
    layout_->addWidget(nicknameBox_);

    passwordBox_ = new QLineEdit(centralWidget());
    passwordBox_->setPlaceholderText("Type your password");
    passwordBox_->setEchoMode(QLineEdit::Password);
    layout_->addWidget(passwordBox_);
}

bool AuthWindow::checkBoxes() const {
    return checkNickname(nicknameBox_->text()) && checkPassword(passwordBox_->text());
}

AuthWindow::AuthWindow(Socket* socket, PlayerInfo& playerInfo, const QString& windowTitle)
: ApplicationWindow(socket, playerInfo, windowTitle) {}
