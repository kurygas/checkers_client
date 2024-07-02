#include <QApplication>
#include "socket.h"
#include "login_screen.h"
#include "lobby.h"
#include "player_info.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Socket socket(&a);
    socket.ConnectToServer();
    PlayerInfo player;
    LoginScreen loginScreen(socket, player);
    Lobby lobby(socket, player, &loginScreen);
    loginScreen.SetLobby(&lobby);
    return QApplication::exec();
}
