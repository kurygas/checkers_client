#include "registration_window.h"

RegistrationWindow::RegistrationWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle)
: AuthWindow(socket, player, windowTitle) {}

void RegistrationWindow::Draw() {
    AuthWindow::Draw();

    registerButton_ = new QPushButton("Register", centralWidget());
    connect(registerButton_, &QPushButton::clicked, this, &RegistrationWindow::SendRegister);
    layout_->addWidget(registerButton_);

    infoLabel_ = new QLabel("", centralWidget());
    layout_->addWidget(infoLabel_);


    backButton_ = new QPushButton("Back", centralWidget());
    connect(backButton_, &QPushButton::clicked, this, &RegistrationWindow::OpenLogin);
    layout_->addWidget(backButton_);
}

void RegistrationWindow::OpenLogin() {
    Close();
    loginWindow_->Open();
}

void RegistrationWindow::ProcessMessage(const Query& query) {
    if (query.Type() == QueryId::Register) {
        ReceiveRegister(query);
    }
}

void RegistrationWindow::ReceiveRegister(const Query& query) {
    const auto result = query.GetId(0);

    if (result == QueryId::Ok) {
        ShowInfo("Successful registration");
        OpenLogin();
        return;
    }
    else if (result == QueryId::AlreadyExist) {
        ShowError("Login already exists");
    }

    infoLabel_->clear();
    registerButton_->setEnabled(true);
    backButton_->setEnabled(true);
}

void RegistrationWindow::SendRegister() {
    if (CheckBoxes()) {
        Query query(QueryId::Register);
        query.PushString(nicknameBox_->text());
        query.PushString(passwordBox_->text());
        socket_->Write(query);
        infoLabel_->setText("Please wait");
        registerButton_->setEnabled(false);
        backButton_->setEnabled(false);
    }
}

void RegistrationWindow::SetLoginWindow(ApplicationWindow* login) {
    loginWindow_ = login;
}