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
    QList<Query> result;
    const auto data = readAll();

    for (uint i = 0; i < data.size(); ++i) {
        QByteArray buffer;
        const auto querySize = Query::ToInt(data[i]);

        for (uint j = 0; j < querySize; ++j) {
            buffer.push_back(data[i + j + 1]);
        }

        result.emplace_back(buffer);
        i += querySize;
    }

    return result;
}