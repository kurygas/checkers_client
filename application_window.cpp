#include "application_window.h"

ApplicationWindow::ApplicationWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle)
: socket_(socket)
, player_(player) {
    setWindowTitle(windowTitle);
    connect(this, &QMainWindow::destroyed, socket_, &Socket::PrepareForClose);
}

void ApplicationWindow::Open() {
    connect(socket_, &QTcpSocket::readyRead, this, &ApplicationWindow::ReceiveMessage);
    Draw();
    show();
}

void ApplicationWindow::Draw() {
    setCentralWidget(new QWidget());
    layout_ = new QVBoxLayout(centralWidget());
    layout_->setAlignment(Qt::AlignHCenter);
}

void ApplicationWindow::Close() {
    disconnect(socket_, &QTcpSocket::readyRead, nullptr, nullptr);
    takeCentralWidget()->deleteLater();
    hide();
}

void ApplicationWindow::ReceiveMessage() {
    if (!isHidden()) {
        const auto& messages = socket_->Read();

        for (const auto& message : messages) {
            ProcessMessage(message);
        }
    }
}

void ApplicationWindow::ShowError(const QString& text) {
    QMessageBox::critical(nullptr, "Checkers Online", text);
}

void ApplicationWindow::ShowInfo(const QString& text) {
    QMessageBox::information(nullptr, "Checkers Online", text);
}

bool ApplicationWindow::CheckNickname(const QString& nickname) {
    if (nickname.size() < 3) {
        ShowError("Nickname must contain at least 3 characters");
        return false;
    }

    return true;
}

bool ApplicationWindow::CheckPassword(const QString &password) {
    if (password.size() < 6) {
        ShowError("Password must contain at least 6 characters");
        return false;
    }

    return true;
}
