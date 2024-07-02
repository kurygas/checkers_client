#include "application_window.h"

ApplicationWindow::ApplicationWindow()
: screenWidth_(QApplication::primaryScreen()->geometry().width()) {
    setWindowState(Qt::WindowMaximized);
}
