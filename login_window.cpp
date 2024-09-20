#include "login_window.h"

LoginWindow::LoginWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle)
: AuthWindow(socket, player, windowTitle) {}

void LoginWindow::setLobbyWindow(LobbyWindow* lobbyWindow) {
    lobbyWindow_ = lobbyWindow;
}

void LoginWindow::setRegisterWindow(RegistrationWindow* registrationWindow) {
    registrationWindow_ = registrationWindow;
}

void LoginWindow::drawWindow() {
    AuthWindow::drawWindow();

    loginButton_ = new QPushButton("Log in", centralWidget());
    connect(loginButton_, &QPushButton::pressed, this, &LoginWindow::sendLogin);
    layout_->addWidget(loginButton_);

    infoLabel_ = new QLabel(centralWidget());
    layout_->addWidget(infoLabel_);

    registerButton_ = new QPushButton("Register", centralWidget());
    connect(registerButton_, &QPushButton::pressed, this, &LoginWindow::openRegistration);
    layout_->addWidget(registerButton_);
}

void LoginWindow::openRegistration() {
    changeWindow(registrationWindow_);
}

void LoginWindow::processMessage(const Query& query) {
    if (query.getType() == QueryId::Login) {
        receiveLogin(query);
    }
}

void LoginWindow::receiveLogin(const Query& query) {
    const auto result = query.getId(0);

    if (result == QueryId::Ok) {
        playerInfo_.rating = query.getInt(1);
        closeWindow();
        lobbyWindow_->openWindow();
        return;
    }
    else if (result == QueryId::NotExist) {
        showError("Login doesn't exist!");
    }
    else if (result == QueryId::WrongPassword) {
        showError("Wrong password!");
    }

    infoLabel_->clear();
    loginButton_->setEnabled(true);
    registerButton_->setEnabled(true);
}

void LoginWindow::sendLogin() {
    if (checkBoxes()) {
        Query query(QueryId::Login);
        playerInfo_.nickname = nicknameBox_->text();
        query.pushString(playerInfo_.nickname);
        query.pushString(passwordBox_->text());
        socket_->writeMessage(query);
        infoLabel_->setText("Please wait");
        loginButton_->setEnabled(false);
        registerButton_->setEnabled(false);
    }
}
