#include "registration_window.h"

RegistrationWindow::RegistrationWindow(Socket* socket, PlayerInfo& player)
: AuthWindow(socket, player) {}

void RegistrationWindow::Draw() {
    AuthWindow::Draw();

    headerLabel_->setText("Registration");

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
    if (query.GetId() == QueryId::Register) {
        ReceiveRegister(query);
    }
}

void RegistrationWindow::ReceiveRegister(const Query& query) {
    const auto& result = query.GetData<QueryId>(0);

    if (result == QueryId::Ok) {
        ShowInfo("Successful registration");
        OpenLogin();
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
        query.PushData(nicknameBox_->text());
        query.PushData(passwordBox_->text());
        socket_->Write(query);
        infoLabel_->setText("Please wait");
        registerButton_->setEnabled(false);
        backButton_->setEnabled(false);
    }
}

void RegistrationWindow::SetLoginWindow(ApplicationWindow* login) {
    loginWindow_ = login;
}
