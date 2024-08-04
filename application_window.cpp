#include "application_window.h"

ApplicationWindow::ApplicationWindow(Socket* socket, PlayerInfo& player)
: socket_(socket)
, player_(player) {
    setWindowTitle("Checkers Online");
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
    headerLabel_ = new QLabel(centralWidget());
    layout_->addWidget(headerLabel_);
}

void ApplicationWindow::Close() {
    disconnect(socket_, &QTcpSocket::readyRead, nullptr, nullptr);
    delete takeCentralWidget();
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
