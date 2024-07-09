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

void Socket::Write(const QList<QString>& message) {
    write('#' + message.join('$').toUtf8());
}

QList<QList<QString>> Socket::Read() {
    return Parse(QString(readAll()));
}
