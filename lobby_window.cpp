#include "lobby_window.h"

LobbyWindow::LobbyWindow(Socket* socket, PlayerInfo& player, const QString& windowTitle)
: ApplicationWindow(socket, player, windowTitle) {}

void LobbyWindow::SetLoginWindow(ApplicationWindow* loginWindow) {
    loginWindow_ = loginWindow;
}

void LobbyWindow::Draw() {
    ApplicationWindow::Draw();

    nicknameLabel_ = new QLabel("Nickname: " + player_.nickname, centralWidget());
    layout_->addWidget(nicknameLabel_);

    ratingLabel_ = new QLabel("Rating: " + QString::number(player_.rating), centralWidget());
    layout_->addWidget(ratingLabel_);

    changeNicknameButton_ = new QPushButton("Change nickname", centralWidget());
    connect(changeNicknameButton_, &QPushButton::pressed, this, &LobbyWindow::SendChangeNickname);
    layout_->addWidget(changeNicknameButton_);

    changePasswordButton_ = new QPushButton("Change password", centralWidget());
    connect(changePasswordButton_, &QPushButton::pressed, this, &LobbyWindow::SendChangePassword);
    layout_->addWidget(changePasswordButton_);

    logoutButton_ = new QPushButton("Log out", centralWidget());
    connect(logoutButton_, &QPushButton::pressed, this, &LobbyWindow::SendLogout);
    layout_->addWidget(logoutButton_);

    searchButton_ = new QPushButton("Find game", centralWidget());
    connect(searchButton_, &QPushButton::pressed, this, &LobbyWindow::SendFindGame);
    layout_->addWidget(searchButton_);

    cancelButton_ = new QPushButton("Stop searching", centralWidget());
    connect(cancelButton_, &QPushButton::pressed, this, &LobbyWindow::SendCancelSearching);
    cancelButton_->hide();
    layout_->addWidget(cancelButton_);

    infoLabel_ = new QLabel(centralWidget());
    layout_->addWidget(infoLabel_);

    searchingTimer_ = new QTimer(centralWidget());
    connect(searchingTimer_, &QTimer::timeout, this, &LobbyWindow::SearchLabelTimeout);
}

void LobbyWindow::ProcessMessage(const Query& query) {
    const auto& id = query.Type();

    if (id == QueryId::StartGame) {
        ReceiveStartGame(query);
    }
    else if (id == QueryId::CancelSearching) {
        ReceiveCancelSearching();
    }
    else if (id == QueryId::ChangePassword) {
        ReceiveChangePassword(query);
    }
    else if (id == QueryId::ChangeNickname) {
        ReceiveChangeNickname(query);
    }
}

void LobbyWindow::SendFindGame() {
    Query query(QueryId::FindGame);
    query.PushUInt(player_.rating / 100);
    socket_->Write(query);
    player_.inSearch = true;
    SearchLabelTimeout();
    EnableButtons(false);
    cancelButton_->show();
}

void LobbyWindow::SearchLabelTimeout() {
    if (player_.inSearch) {
        ++timeInSearch_;
        auto minutes = QString::number(timeInSearch_ / 60);
        minutes = QString(2 - minutes.size(), '0') + minutes;
        auto seconds = QString::number(timeInSearch_ % 60);
        seconds = QString(2 - seconds.size(), '0') + seconds;
        infoLabel_->setText("Queue time: " + minutes + ':' + seconds);
        searchingTimer_->start(1s);
    }
    else {
        EnableButtons(true);
        infoLabel_->clear();
        timeInSearch_ = 0;
    }
}

void LobbyWindow::ReceiveStartGame(const Query &query) {
    qDebug() << "pobeda";
}

void LobbyWindow::SendCancelSearching() {
    socket_->Write(Query(QueryId::CancelSearching));
}

void LobbyWindow::ReceiveCancelSearching() {
    player_.inSearch = false;
}

void LobbyWindow::EnableButtons(const bool state) {
    changeNicknameButton_->setEnabled(state);
    changePasswordButton_->setEnabled(state);
    logoutButton_->setEnabled(state);
    searchButton_->setEnabled(state);
}

void LobbyWindow::SendLogout() {
    socket_->Write(Query(QueryId::Logout));
    Close();
    loginWindow_->Open();
}

void LobbyWindow::SendChangeNickname() {
    auto newNickname = QInputDialog::getText(centralWidget(), "Changing nickname", "Type new nickname");

    if (newNickname == player_.nickname) {
        ShowError("The new nickname must differ from your current nickname");
        return;
    }

    if (!CheckNickname(newNickname)) {
        return;
    }

    EnableButtons(false);
    player_.newNickname = std::move(newNickname);
    Query query(QueryId::ChangeNickname);
    query.PushString(player_.newNickname);
    socket_->Write(query);
}

void LobbyWindow::ReceiveChangeNickname(const Query& query) {
    const auto result = query.GetId(0);

    if (result == QueryId::AlreadyExist) {
        ShowError("This nickname already exist");
    }
    else if (result == QueryId::Ok) {
        player_.nickname = player_.newNickname;
        nicknameLabel_->setText(player_.nickname);
        ShowInfo("Your nickname has successfully changed");
    }

    player_.newNickname.clear();
    EnableButtons(true);
}

void LobbyWindow::SendChangePassword() {
    auto newPassword = QInputDialog::getText(centralWidget(), "Changing password", "Type new password");

    if (!CheckPassword(newPassword)) {
        return;
    }

    EnableButtons(false);
    Query query(QueryId::ChangePassword);
    query.PushString(newPassword);
    socket_->Write(query);
}

void LobbyWindow::ReceiveChangePassword(const Query& query) {
    const auto result = query.GetId(0);

    if (result == QueryId::Same) {
        ShowError("The new password must differ from your current password");
    }
    else if (result == QueryId::Ok) {
        ShowInfo("Your password has successfully changed");
    }

    EnableButtons(true);
}

