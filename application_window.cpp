#include "application_window.h"

ApplicationWindow::ApplicationWindow(Socket* socket, PlayerInfo& player)
: screenWidth_(QApplication::primaryScreen()->geometry().width())
, screenHeight_(QApplication::primaryScreen()->geometry().height())
, socket_(socket)
, player_(player) {
    setWindowState(Qt::WindowMaximized);
    connect(this, &QMainWindow::destroyed, socket_, &Socket::PrepareForClose);
}

void ApplicationWindow::Open() {
    connect(socket_, &QTcpSocket::readyRead, this, &ApplicationWindow::ReceiveMessage);
    isActive_ = true;
    Draw();
    show();
}

void ApplicationWindow::Close() {
    disconnect(socket_, &QTcpSocket::readyRead, nullptr, nullptr);
    isActive_ = false;
    delete takeCentralWidget();
    hide();
}

void ApplicationWindow::ReceiveMessage() {
    if (isActive_) {
        auto messages = socket_->Read();

        for (const auto& message : messages) {
            ProcessMessage(message);
        }
    }
}
