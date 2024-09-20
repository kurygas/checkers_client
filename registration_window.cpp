#include "registration_window.h"

RegistrationWindow::RegistrationWindow(Socket* socket, PlayerInfo& playerInfo, const QString& windowTitle)
: AuthWindow(socket, playerInfo, windowTitle) {}

void RegistrationWindow::drawWindow() {
    AuthWindow::drawWindow();

    registerButton_ = new QPushButton("Register", centralWidget());
    connect(registerButton_, &QPushButton::clicked, this, &RegistrationWindow::sendRegister);
    layout_->addWidget(registerButton_);

    infoLabel_ = new QLabel("", centralWidget());
    layout_->addWidget(infoLabel_);


    backButton_ = new QPushButton("Back", centralWidget());
    connect(backButton_, &QPushButton::clicked, this, &RegistrationWindow::openLogin);
    layout_->addWidget(backButton_);
}

void RegistrationWindow::openLogin() {
    changeWindow(loginWindow_);
}

void RegistrationWindow::processMessage(const Query& query) {
    if (query.getType() == QueryId::Register) {
        receiveRegister(query);
    }
}

void RegistrationWindow::receiveRegister(const Query& query) {
    const auto result = query.getId(0);

    if (result == QueryId::Ok) {
        showInfo("Successful registration");
        openLogin();
        return;
    }
    else if (result == QueryId::AlreadyExist) {
        showError("Login already exists");
    }

    infoLabel_->clear();
    registerButton_->setEnabled(true);
    backButton_->setEnabled(true);
}

void RegistrationWindow::sendRegister() {
    if (checkBoxes()) {
        Query query(QueryId::Register);
        query.pushString(nicknameBox_->text());
        query.pushString(passwordBox_->text());
        socket_->writeMessage(query);
        infoLabel_->setText("Please wait");
        registerButton_->setEnabled(false);
        backButton_->setEnabled(false);
    }
}

void RegistrationWindow::setLoginWindow(LoginWindow* login) {
    loginWindow_ = login;
}
