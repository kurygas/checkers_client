#pragma once
#include <QTcpSocket>
#include <QApplication>
#include <QMessageBox>
#include <string>
#include <exception>
#include <memory>

class ConnectionError: public std::exception {
public:
    [[nodiscard]] char* what() const noexcept override;
};

class Socket : public QTcpSocket {
public:
    explicit Socket(QApplication* app);
    void ConnectToServer();
    void Write(const std::string& data);
    std::string Read();
    static void ConnectionLost();
};