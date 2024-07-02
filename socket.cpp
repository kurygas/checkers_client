#include "socket.h"

char* ConnectionError::what() const noexcept {
    return strdup("Connection lost");
}

Socket::Socket(QApplication* app)
: QTcpSocket(app) {}

void Socket::ConnectToServer() {
    connectToHost(QHostAddress::LocalHost, 8080);

    if (!waitForConnected()) {
        ConnectionLost();
    }

    connect(this, &QTcpSocket::disconnected, this, &Socket::ConnectionLost);
}

void Socket::Write(const std::string& data) {
    write(data.c_str());

    if (!QAbstractSocket::waitForBytesWritten()) {
        ConnectionLost();
    }
}

std::string Socket::Read() {
    if (!QAbstractSocket::waitForReadyRead()) {
        ConnectionLost();
    }

    return readAll().toStdString();
}

void Socket::ConnectionLost() {
    QMessageBox::critical(nullptr, "Error", "Connection lost!");
    exit(0);
}