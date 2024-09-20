#include "application_window.h"

ApplicationWindow::ApplicationWindow(Socket* socket, PlayerInfo& playerInfo, const QString& windowTitle)
: socket_(socket)
, playerInfo(playerInfo) {
    setWindowTitle(windowTitle);
    connect(this, &QMainWindow::destroyed, socket_, &Socket::prepareForClose);
}

void ApplicationWindow::openWindow() {
    connect(socket_, &QTcpSocket::readyRead, this, &ApplicationWindow::receiveMessage);
    drawWindow();
    show();
}

void ApplicationWindow::drawWindow() {
    setCentralWidget(new QWidget());
    layout_ = new QVBoxLayout(centralWidget());
    layout_->setAlignment(Qt::AlignHCenter);
}

void ApplicationWindow::closeWindow() {
    disconnect(socket_, &QTcpSocket::readyRead, nullptr, nullptr);
    takeCentralWidget()->deleteLater();
    hide();
}

void ApplicationWindow::receiveMessage() {
    if (!isHidden()) {
        const auto& messages = socket_->readMessage();

        for (const auto& message : messages) {
            processMessage(message);
        }
    }
}

void ApplicationWindow::showError(const QString& text) {
    QMessageBox::critical(nullptr, "Checkers Online", text);
}

void ApplicationWindow::showInfo(const QString& text) {
    QMessageBox::information(nullptr, "Checkers Online", text);
}

bool ApplicationWindow::checkNickname(const QString& nickname) {
    if (nickname.size() < 3) {
        showError("Nickname must contain at least 3 characters");
        return false;
    }

    return true;
}

bool ApplicationWindow::checkPassword(const QString &password) {
    if (password.size() < 6) {
        showError("Password must contain at least 6 characters");
        return false;
    }

    return true;
}

void ApplicationWindow::changeWindow(ApplicationWindow* newWindow) {
    closeWindow();
    newWindow->openWindow();
}
