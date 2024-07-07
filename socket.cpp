#include "socket.h"

char* ConnectionError::what() const noexcept {
    return strdup("Connection lost");
}

void Socket::ConnectToServer() {
    connectToHost(QHostAddress::LocalHost, 8080);

    if (!waitForConnected()) {
        ConnectionLost();
    }

    connectionLostCall_ = connect(this, &QTcpSocket::disconnected, this, &Socket::ConnectionLost);
}

void Socket::Write(const QString& data) {
    write(data.toUtf8());

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
    throw ConnectionError();
}

void Socket::PrepareForClose() {
    disconnect(connectionLostCall_);
}
