#pragma once

#include <QTcpSocket>
#include <QMessageBox>
#include <QApplication>

#include "query.h"

class Socket : public QTcpSocket {
public:
    explicit Socket(QApplication* parent);

    void connectToServer();
    void prepareForClose();

    static void connectionLost();

    void writeMessage(const Query& message);
    QList<Query> readMessage();
};
