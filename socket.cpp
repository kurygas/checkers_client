#include "socket.h"

Socket::Socket(QApplication* parent)
: QTcpSocket(parent) {
    connect(this, &QTcpSocket::disconnected, this, &Socket::ConnectionLost);
}

void Socket::ConnectToServer() {
    connectToHost(QHostAddress::LocalHost, 8080);

    if (!waitForConnected()) {
        ConnectionLost();
    }

   connect(this, &QTcpSocket::disconnected, this, &Socket::ConnectionLost);
}

void Socket::ConnectionLost() {
    QMessageBox::critical(nullptr, "Error", "Connection lost!");
    exit(0);
}

void Socket::PrepareForClose() {
    disconnect(this, &QTcpSocket::disconnected, nullptr, nullptr);
}

void Socket::Write(const Query& message) {
    write(message.ToBytes());
}

QList<Query> Socket::Read() {
    QByteArray buffer;
    QList<Query> result;

    for (const auto& byte : readAll()) {
        if (Query::ToType(byte) == QueryId::Query) {
            if (!buffer.isEmpty()) {
                result.emplace_back(buffer);
                buffer.clear();
            }
        }
        else {
            buffer.push_back(byte);
        }
    }

    result.emplace_back(buffer);
    return result;
}
