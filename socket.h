#pragma once
#include <QTcpSocket>
#include <QApplication>
#include <QMessageBox>
#include "query.h"

class Socket : public QTcpSocket {
public:
    explicit Socket(QApplication* parent);
    void ConnectToServer();
    void PrepareForClose();
    static void ConnectionLost();

    void Write(const Query& message);
    QList<Query> Read();
};
