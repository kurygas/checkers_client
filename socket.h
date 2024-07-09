#pragma once
#include <QTcpSocket>
#include <QApplication>
#include <QMessageBox>
#include "utility_functions.h"

class Socket : public QTcpSocket {
public:
    explicit Socket(QApplication* parent);
    void ConnectToServer();
    void PrepareForClose();
    static void ConnectionLost();

    void Write(const QList<QString>& message);
    QList<QList<QString>> Read();
};
