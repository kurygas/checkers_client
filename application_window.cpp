#include "application_window.h"

ApplicationWindow::ApplicationWindow(Socket& socket, PlayerInfo& player)
: screenWidth_(QApplication::primaryScreen()->geometry().width())
, screenHeight_(QApplication::primaryScreen()->geometry().height())
, socket_(socket)
, player_(player) {
    setWindowState(Qt::WindowMaximized);
    connect(this, &QMainWindow::destroyed, &socket, &Socket::PrepareForClose);
}
