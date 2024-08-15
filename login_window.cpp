#include "login_window.h"

LoginWindow::LoginWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle)
: AuthWindow(socket, player, windowTitle) {}

void LoginWindow::SetLobbyWindow(LobbyWindow* lobby) {
    lobbyWindow_ = lobby;
}

void LoginWindow::SetRegisterWindow(RegistrationWindow* reg) {
    registrationWindow_ = reg;
}

void LoginWindow::Draw() {
    AuthWindow::Draw();

    loginButton_ = new QPushButton("Log in", centralWidget());
    connect(loginButton_, &QPushButton::pressed, this, &LoginWindow::SendLogin);
    layout_->addWidget(loginButton_);

    infoLabel_ = new QLabel(centralWidget());
    layout_->addWidget(infoLabel_);

    registerButton_ = new QPushButton("Register", centralWidget());
    connect(registerButton_, &QPushButton::pressed, this, &LoginWindow::OpenRegistration);
    layout_->addWidget(registerButton_);
}

void LoginWindow::OpenRegistration() {
    Close();
    registrationWindow_->Open();
}

void LoginWindow::ProcessMessage(const Query& query) {
    if (query.Type() == QueryId::Login) {
        ReceiveLogin(query);
    }
}

void LoginWindow::ReceiveLogin(const Query& query) {
    const auto result = query.GetId(0);

    if (result == QueryId::Ok) {
        player_.rating = query.GetInt(1);
        Close();
        lobbyWindow_->Open();
        return;
    }
    else if (result == QueryId::NotExist) {
        ShowError("Login doesn't exist!");
    }
    else if (result == QueryId::WrongPassword) {
        ShowError("Wrong password!");
    }

    infoLabel_->clear();
    loginButton_->setEnabled(true);
    registerButton_->setEnabled(true);
}

void LoginWindow::SendLogin() {
    if (CheckBoxes()) {
        Query query(QueryId::Login);
        player_.nickname = nicknameBox_->text();
        query.PushString(player_.nickname);
        query.PushString(passwordBox_->text());
        socket_->Write(query);
        infoLabel_->setText("Please wait");
        loginButton_->setEnabled(false);
        registerButton_->setEnabled(false);
    }
}
