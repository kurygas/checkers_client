#pragma once
#include <QTcpSocket>
#include <QApplication>
#include <QMessageBox>
#include <QMetaObject>
#include <exception>

class ConnectionError: public std::exception {
public:
    [[nodiscard]] char* what() const noexcept override;
};

class Socket : public QTcpSocket {
public:
    void ConnectToServer();
    void Write(const QString& data);
    std::string Read();
    void PrepareForClose();
    static void ConnectionLost();

private:
    QMetaObject::Connection connectionLostCall_;
};