#include "socket.h"

Socket::Socket(QApplication* parent)
: QTcpSocket(parent) {
    connect(this, &QTcpSocket::disconnected, this, &Socket::connectionLost);
}

void Socket::connectToServer() {
    connectToHost(QHostAddress::LocalHost, 8080);

    if (!waitForConnected()) {
        connectionLost();
    }

   connect(this, &QTcpSocket::disconnected, this, &Socket::connectionLost);
}

void Socket::connectionLost() {
    QMessageBox::critical(nullptr, "Error", "Connection lost!");
    exit(0);
}

void Socket::prepareForClose() {
    disconnect(this, &QTcpSocket::disconnected, nullptr, nullptr);
}

void Socket::writeMessage(const Query& message) {
    write(message.toBytes());
}

QList<Query> Socket::readMessage() {
    QList<Query> result;
    const auto data = readAll();

    for (auto i = 0; i < data.size(); i += 2) {
        QByteArray buffer;
        const auto querySize = (Query::ToInt(data[i]) << 8) + Query::ToInt(data[i + 1]);

        for (auto j = 0; j < querySize; ++j) {
            buffer.push_back(data[i + j + 2]);
        }

        result.emplace_back(buffer);
        i += querySize;
    }

    return result;
}
