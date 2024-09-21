#include "lobby_window.h"

LobbyWindow::LobbyWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle)
: ApplicationWindow(socket, player, windowTitle) {}

void LobbyWindow::setLoginWindow(LoginWindow* loginWindow) {
    loginWindow_ = loginWindow;
}

void LobbyWindow::setGameWindow(GameWindow* gameWindow) {
    gameWindow_ = gameWindow;
}

void LobbyWindow::drawWindow() {
    ApplicationWindow::drawWindow();

    nicknameLabel_ = new QLabel("Nickname: " + playerInfo_.nickname, centralWidget());
    layout_->addWidget(nicknameLabel_);

    ratingLabel_ = new QLabel("Rating: " + QString::number(playerInfo_.rating), centralWidget());
    layout_->addWidget(ratingLabel_);

    changeNicknameButton_ = new QPushButton("Change nickname", centralWidget());
    connect(changeNicknameButton_, &QPushButton::pressed, this, &LobbyWindow::sendChangeNickname);
    layout_->addWidget(changeNicknameButton_);

    changePasswordButton_ = new QPushButton("Change password", centralWidget());
    connect(changePasswordButton_, &QPushButton::pressed, this, &LobbyWindow::sendChangePassword);
    layout_->addWidget(changePasswordButton_);

    logoutButton_ = new QPushButton("Log out", centralWidget());
    connect(logoutButton_, &QPushButton::pressed, this, &LobbyWindow::sendLogout);
    layout_->addWidget(logoutButton_);

    searchButton_ = new QPushButton("Find game", centralWidget());
    connect(searchButton_, &QPushButton::pressed, this, &LobbyWindow::sendFindGame);
    layout_->addWidget(searchButton_);

    cancelButton_ = new QPushButton("Stop searching", centralWidget());
    connect(cancelButton_, &QPushButton::pressed, this, &LobbyWindow::sendCancelSearching);
    cancelButton_->hide();
    layout_->addWidget(cancelButton_);

    infoLabel_ = new QLabel(centralWidget());
    infoLabel_->hide();
    layout_->addWidget(infoLabel_);

    searchingTimer_ = new QTimer(centralWidget());
    connect(searchingTimer_, &QTimer::timeout, this, &LobbyWindow::searchLabelTimeout);
}

void LobbyWindow::processMessage(const Query& query) {
    const auto id = query.getType();

    if (id == QueryId::StartGame) {
        receiveStartGame(query);
    }
    else if (id == QueryId::CancelSearching) {
        receiveCancelSearching();
    }
    else if (id == QueryId::ChangePassword) {
        receiveChangePassword(query);
    }
    else if (id == QueryId::ChangeNickname) {
        receiveChangeNickname(query);
    }
}

void LobbyWindow::sendFindGame() {
    Query query(QueryId::FindGame);
    query.pushShort(1);
    query.pushInt(playerInfo_.rating / 100);
    socket_->writeMessage(query);
    inSearch_ = true;
    searchLabelTimeout();
    enableButtons(false);
    cancelButton_->show();
    infoLabel_->show();
}

void LobbyWindow::searchLabelTimeout() {
    if (inSearch_) {
        ++timeInSearch_;
        auto minutes = QString::number(timeInSearch_ / 60);
        minutes = QString(2 - minutes.size(), '0') + minutes;
        auto seconds = QString::number(timeInSearch_ % 60);
        seconds = QString(2 - seconds.size(), '0') + seconds;
        infoLabel_->setText("Queue time: " + minutes + ':' + seconds);
        searchingTimer_->start(1s);

        if (timeInSearch_ % 10 == 0) {
            const auto playerDivision = playerInfo_.rating / 100;
            const auto divisionAddition = timeInSearch_ / 10;
            Query query(QueryId::FindGame);

            if (playerDivision >= divisionAddition) {
                query.pushShort(2);
                query.pushInt(playerDivision - divisionAddition);
            }
            else {
                query.pushShort(1);
            }

            query.pushInt(playerDivision + divisionAddition);
            socket_->writeMessage(query);
        }
    }
}

void LobbyWindow::receiveStartGame(const Query& query) {
    playerInfo_.enemyNickname = query.getString(0);
    playerInfo_.enemyRating = query.getInt(1);
    playerInfo_.color = query.getId(2) == QueryId::White ? Color::white : Color::black;
    changeWindow(gameWindow_);
}

void LobbyWindow::sendCancelSearching() {
    socket_->writeMessage(Query(QueryId::CancelSearching));
}

void LobbyWindow::receiveCancelSearching() {
    inSearch_ = false;
    enableButtons(true);
    infoLabel_->clear();
    timeInSearch_ = 0;
    cancelButton_->hide();
    infoLabel_->hide();
}

void LobbyWindow::enableButtons(const bool state) {
    changeNicknameButton_->setEnabled(state);
    changePasswordButton_->setEnabled(state);
    logoutButton_->setEnabled(state);
}

void LobbyWindow::sendLogout() {
    socket_->writeMessage(Query(QueryId::Logout));
    changeWindow(loginWindow_);
}

void LobbyWindow::sendChangeNickname() {
    auto newNickname = QInputDialog::getText(centralWidget(), "Changing nickname", "getType new nickname");

    if (newNickname == playerInfo_.nickname) {
        showError("The new nickname must differ from your current nickname");
        return;
    }

    if (!checkNickname(newNickname)) {
        return;
    }

    enableButtons(false);
    playerInfo_.newNickname = std::move(newNickname);
    Query query(QueryId::ChangeNickname);
    query.pushString(playerInfo_.newNickname);
    socket_->writeMessage(query);
}

void LobbyWindow::receiveChangeNickname(const Query& query) {
    const auto result = query.getId(0);

    if (result == QueryId::AlreadyExist) {
        showError("This nickname already exist");
    }
    else if (result == QueryId::Ok) {
        playerInfo_.nickname = playerInfo_.newNickname;
        nicknameLabel_->setText(playerInfo_.nickname);
        showInfo("Your nickname has successfully changed");
    }

    playerInfo_.newNickname.clear();
    enableButtons(true);
}

void LobbyWindow::sendChangePassword() {
    auto newPassword = QInputDialog::getText(centralWidget(), "Changing password", "getType new password");

    if (!checkPassword(newPassword)) {
        return;
    }

    enableButtons(false);
    Query query(QueryId::ChangePassword);
    query.pushString(newPassword);
    socket_->writeMessage(query);
}

void LobbyWindow::receiveChangePassword(const Query& query) {
    const auto result = query.getId(0);

    if (result == QueryId::Same) {
        showError("The new password must differ from your current password");
    }
    else if (result == QueryId::Ok) {
        showInfo("Your password has successfully changed");
    }

    enableButtons(true);
}
