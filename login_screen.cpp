#include "login_screen.h"

LoginScreen::LoginScreen(Socket& socket, PlayerInfo& player)
: socket_(socket)
, player_(player) {
    DrawWindow();
}

void LoginScreen::OpenLogin() {
    headerLabel_->setText("Checkers Online");
    activeButton_->setText("Log in");
    connect(activeButton_, &QPushButton::pressed, this, &LoginScreen::Login);
    swapButton_->setText("Register");
    connect(swapButton_, &QPushButton::pressed, this, &LoginScreen::OpenRegistration);
    connectLabel_->hide();
    ClearBoxes();
}

void LoginScreen::OpenRegistration() {
    headerLabel_->setText("Registration");
    activeButton_->setText("Register");
    connect(activeButton_, &QPushButton::pressed, this, &LoginScreen::Register);
    swapButton_->setText("Back");
    connect(swapButton_, &QPushButton::pressed, this, &LoginScreen::OpenLogin);
    connectLabel_->hide();
    ClearBoxes();
}

void LoginScreen::Request(const std::string& type) {
    socket_.Write((type + '$' + loginBox_->text().toStdString() + '$' + passwordBox_->text().toStdString()));
    connectLabel_->show();
    connectLabel_->setText(socket_.Read().c_str());

    if (connectLabel_->text() != "Success") {
        connectLabel_->setStyleSheet("QLabel {color: red;}");
    }
    else {
        EraseWindow();
    }
}

void LoginScreen::Login() {
    Request("login");
}

void LoginScreen::Register() {
    Request("register");
}

void LoginScreen::ClearBoxes() {
    loginBox_->setText("");
    passwordBox_->setText("");
}

void LoginScreen::SetLobby(Lobby* lobby) {
    lobby_ = lobby;
}

void LoginScreen::DrawWindow() {
    headerLabel_ = new QLabel(this);
    headerLabel_->setFont(QFont("Arial", 50));
    headerLabel_->setGeometry(0, 0, screenWidth_, 250);
    headerLabel_->setAlignment(Qt::AlignCenter);

    loginBox_ = new QLineEdit(this);
    loginBox_->setGeometry((screenWidth_ - 300) / 2, 300, 300, 50);
    loginBox_->setPlaceholderText("Type your login");

    passwordBox_ = new QLineEdit(this);
    passwordBox_->setGeometry((screenWidth_ - 300) / 2, 360, 300, 50);
    passwordBox_->setPlaceholderText("Type your password");
    passwordBox_->setEchoMode(QLineEdit::Password);

    activeButton_ = new QPushButton(this);
    activeButton_->setGeometry((screenWidth_ - 300) / 2, 420, 300, 50);

    connectLabel_ = new QLabel(this);
    connectLabel_->setAlignment(Qt::AlignCenter);
    connectLabel_->setGeometry((screenWidth_ - 300) / 2, 480, 300, 50);

    swapButton_ = new QPushButton(this);
    swapButton_->setGeometry((screenWidth_ - 300) / 2, 540, 300, 50);

    OpenLogin();
    show();
}

void LoginScreen::EraseWindow() {
    delete headerLabel_;
    delete loginBox_;
    delete passwordBox_;
    delete activeButton_;
    delete connectLabel_;
    delete swapButton_;

    hide();
}
