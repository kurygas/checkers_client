#include "application.h"

int main(int argc, char* argv[]) {
    Application app(argc, argv);
    Application app1(argc, argv);
    return Application::exec();
}