#include "lobby_window.h"

LobbyWindow::LobbyWindow(Socket* socket, PlayerInfo& player)
: ApplicationWindow(socket, player) {}

void LobbyWindow::SetLoginWindow(ApplicationWindow* loginWindow) {
    loginWindow_ = loginWindow;
}

void LobbyWindow::Draw() {
    ApplicationWindow::Draw();

    nicknameLabel_ = new QLabel("Nickname: " + player_.GetNickname(), centralWidget());
    layout_->addWidget(nicknameLabel_);

    ratingLabel_ = new QLabel("Rating: " + QString::number(player_.GetRating()), centralWidget());
    layout_->addWidget(ratingLabel_);

    changeNicknameButton_ = new QPushButton("Change nickname", centralWidget());
    layout_->addWidget(changeNicknameButton_);

    changePasswordButton_ = new QPushButton("Change password", centralWidget());
    layout_->addWidget(changePasswordButton_);

    logOutButton_ = new QPushButton("Log out", centralWidget());
    layout_->addWidget(logOutButton_);

    searchButton_ = new QPushButton("Find game", centralWidget());
    layout_->addWidget(searchButton_);

    cancelButton_ = new QPushButton("Stop searching", centralWidget());
    cancelButton_->hide();
    layout_->addWidget(cancelButton_);

    infoLabel_ = new QLabel(centralWidget());
    layout_->addWidget(infoLabel_);

    searchingTimer_ = new QTimer(centralWidget());
    connect(searchingTimer_, &QTimer::timeout, this, &LobbyWindow::SearchLabelTimeout);
}

void LobbyWindow::OpenLogin() {
    if (!player_.HasEnemy()) {
        Close();
        loginWindow_->Open();
    }
}

void LobbyWindow::ProcessMessage(const Query& query) {
    const auto& id = query.GetId();

    if (id == QueryId::StartGame) {
        ReceiveStartGame(query);
    }
    else if (id == QueryId::CancelSearching) {
        ReceiveCancelSearching();
    }
}

void LobbyWindow::SendFindGame() {
    Query query(QueryId::FindGame);
    query.PushData(player_.GetRating() / 100);
    socket_->Write(query);
    player_.SetSearch(true);
    searchingTimer_->start(1s);
    searchButton_->setEnabled(false);
    changeNicknameButton_->setEnabled(false);
    changePasswordButton_->setEnabled(false);
}

void LobbyWindow::SearchLabelTimeout() {
    if (player_.InSearch()) {
        ++timeInSearch_;
        infoLabel_->setText(QString::number(timeInSearch_ / 60) + ':' + QString::number(timeInSearch_ % 60));
        searchingTimer_->start(1s);
    }
    else {
        infoLabel_->clear();
        timeInSearch_ = 0;
    }
}

void LobbyWindow::ReceiveStartGame(const Query &query) {
    qDebug() << "pobeda";
}

void LobbyWindow::SendCancelSearching() {
    if (!player_.HasEnemy()) {
        const Query query(QueryId::CancelSearching);
        socket_->Write(query);
    }
}

void LobbyWindow::ReceiveCancelSearching() {
    if (!player_.HasEnemy()) {
        player_.SetSearch(false);
        searchButton_->setEnabled(true);
        changeNicknameButton_->setEnabled(true);
        changePasswordButton_->setEnabled(true);
    }
}
