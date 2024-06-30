#include <QApplication>
#include "login_screen.h"
#include "lobby.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    LoginScreen ls;
    return QApplication::exec();
}
