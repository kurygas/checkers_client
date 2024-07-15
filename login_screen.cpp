#include "login_screen.h"

LoginScreen::LoginScreen(const QString& windowTitle, Socket* socket, PlayerInfo& player)
: ApplicationWindow(socket, player, windowTitle) {}

void LoginScreen::OpenLogin() {
    headerLabel_->setText("Checkers Online");
    activeButton_->setText("Log in");
    disconnect(activeButton_, &QPushButton::pressed, nullptr, nullptr);
    connect(activeButton_, &QPushButton::pressed, this, &LoginScreen::SendLogin);
    swapButton_->setText("Register");
    connect(swapButton_, &QPushButton::pressed, this, &LoginScreen::OpenRegistration);
    infoLabel_->hide();
    ClearBoxes();
}

void LoginScreen::OpenRegistration() {
    headerLabel_->setText("Registration");
    activeButton_->setText("Register");
    disconnect(activeButton_, &QPushButton::pressed, nullptr, nullptr);
    connect(activeButton_, &QPushButton::pressed, this, &LoginScreen::SendRegister);
    swapButton_->setText("Back");
    connect(swapButton_, &QPushButton::pressed, this, &LoginScreen::OpenLogin);
    infoLabel_->hide();
    ClearBoxes();
}

void LoginScreen::ClearBoxes() {
    loginBox_->clear();
    passwordBox_->clear();
}

void LoginScreen::SetLobbyScreen(ApplicationWindow* lobby) {
    lobby_ = lobby;
}

void LoginScreen::Draw() {
    headerLabel_ = new QLabel(centralWidget());
    headerLabel_->setFont(QFont("Arial", 50));
    headerLabel_->setGeometry(0, 0, screenWidth_, 250);
    headerLabel_->setAlignment(Qt::AlignCenter);

    loginBox_ = new QLineEdit(centralWidget());
    loginBox_->setGeometry((screenWidth_ - 300) / 2, 300, 300, 50);
    loginBox_->setPlaceholderText("Type your login");

    passwordBox_ = new QLineEdit(centralWidget());
    passwordBox_->setGeometry((screenWidth_ - 300) / 2, 360, 300, 50);
    passwordBox_->setPlaceholderText("Type your password");
    passwordBox_->setEchoMode(QLineEdit::Password);

    activeButton_ = new QPushButton(centralWidget());
    activeButton_->setGeometry((screenWidth_ - 300) / 2, 420, 300, 50);

    infoLabel_ = new QLabel(centralWidget());
    infoLabel_->setAlignment(Qt::AlignCenter);
    infoLabel_->setGeometry((screenWidth_ - 300) / 2, 480, 300, 50);

    swapButton_ = new QPushButton(centralWidget());
    swapButton_->setGeometry((screenWidth_ - 300) / 2, 540, 300, 50);

    OpenLogin();
}

void LoginScreen::ShowError() {
    infoLabel_->setStyleSheet("QLabel {color: red;}");
    infoLabel_->show();
}

void LoginScreen::ShowSuccess() {
    infoLabel_->setStyleSheet("QLabel {color: green;}");
    infoLabel_->show();
}

void LoginScreen::ProcessMessage(const Query& query) {
    if (query.GetId() == QueryId::Login) {
        ReceiveLogin(query);
    }
    else if (query.GetId() == QueryId::Register) {
        ReceiveRegister(query);
    }
}

void LoginScreen::ReceiveLogin(const Query& query) {
    EnableButtons();

    if (query.GetIdInfo(0) == QueryId::Ok) {
        player_.SetRating(query.GetStringInfo(1).toInt());
        Close();
        lobby_->Open();
    }
    else if (query.GetIdInfo(0) == QueryId::NotExist) {
        infoLabel_->setText("Login doesn't exist!");
        ShowError();
    }
    else if (query.GetIdInfo(0) == QueryId::WrongPassword) {
        infoLabel_->setText("Wrong password!");
        ShowError();
    }
}

void LoginScreen::ReceiveRegister(const Query& query) {
    EnableButtons();

    if (query.GetIdInfo(0) == QueryId::Ok) {
        OpenLogin();
        infoLabel_->setText("Successful registration");
        ShowSuccess();
    }
    else if (query.GetIdInfo(0) == QueryId::AlreadyExist) {
        infoLabel_->setText("Login already exists");
        ShowError();
    }
}

bool LoginScreen::CheckBoxesInfo() {
    auto login = loginBox_->text();
    auto password = passwordBox_->text();

    if (login.size() < 3) {
        infoLabel_->setText("Login must contain at least 3 characters");
        ShowError();
        return false;
    }

    if (password.size() < 6) {
        infoLabel_->setText("Password must contain at least 6 characters");
        ShowError();
        return false;
    }

    return true;
}

void LoginScreen::SendLogin() {
    if (CheckBoxesInfo()) {
        Query query(QueryId::Login);
        auto login = loginBox_->text();
        player_.SetNickname(login);
        query.PushInfo(login);
        query.PushInfo(passwordBox_->text());
        socket_->Write(query);
        infoLabel_->setText("Please wait");
        ShowWaitMessage();
    }
}

void LoginScreen::SendRegister() {
    if (CheckBoxesInfo()) {
        Query query(QueryId::Register);
        query.PushInfo(loginBox_->text());
        query.PushInfo(passwordBox_->text());
        socket_->Write(query);
        infoLabel_->setText("Please wait");
        ShowWaitMessage();
    }
}

void LoginScreen::ShowWaitMessage() {
    infoLabel_->setText("Please wait");
    infoLabel_->setStyleSheet("QLabel {color: black;}");
    infoLabel_->show();
    activeButton_->setEnabled(false);
    swapButton_->setEnabled(false);
}

void LoginScreen::EnableButtons() {
    activeButton_->setEnabled(true);
    swapButton_->setEnabled(true);
}
