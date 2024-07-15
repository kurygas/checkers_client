#include "lobby_screen.h"

LobbyScreen::LobbyScreen(const QString& windowTitle, Socket* socket, PlayerInfo& player, ApplicationWindow* loginScreen)
: ApplicationWindow(socket, player, windowTitle)
, loginScreen_(loginScreen) {}

void LobbyScreen::Draw() {
    leftContainer_ = new QWidget(centralWidget());
    leftContainer_->setGeometry(10, 10, screenWidth_ / 2 - 10, screenHeight_ - 20);

    leftLayout_ = new QVBoxLayout(leftContainer_);
    leftLayout_->setSpacing(20);
    leftLayout_->setAlignment(Qt::AlignTop);

    nicknameLabel_ = new QLabel(player_.GetNickname());
    nicknameLabel_->setFont(QFont("Arial", 20));
    leftLayout_->addWidget(nicknameLabel_);

    ratingLabel_ = new QLabel("Rating: " + QString::number(player_.GetRating()));
    ratingLabel_->setFont(QFont("Arial", 20));
    leftLayout_->addWidget(ratingLabel_);

    changeNicknameButton_ = new QPushButton("Change nickname");
    connect(changeNicknameButton_, &QPushButton::pressed, this, &LobbyScreen::SendChangeNickname);
    leftLayout_->addWidget(changeNicknameButton_);

    changePasswordButton_ = new QPushButton("Change nickname");
    connect(changeNicknameButton_, &QPushButton::pressed, this, &LobbyScreen::SendChangePassword);
    leftLayout_->addWidget(changePasswordButton_);

    AddLine();

    createButton_ = new QPushButton("Create new room", centralWidget());
    createButton_->setGeometry(screenWidth_ / 2, 10, screenWidth_ / 4 - 5, 50);
    connect(createButton_, &QPushButton::pressed, this, &LobbyScreen::SendCreateRoom);

    refreshButton_ = new QPushButton("Refresh room list", centralWidget());
    refreshButton_->setGeometry(screenWidth_ / 4 * 3 - 5, 10, screenWidth_ / 4 - 5, 50);
    connect(refreshButton_, &QPushButton::pressed, this, &LobbyScreen::SendRoomList);

    buttonContainer_ = new QWidget(centralWidget());
    buttonLayout_ = new QVBoxLayout(buttonContainer_);

    auto scrollArea_ = new QScrollArea(centralWidget());
    scrollArea_->setGeometry(screenWidth_ / 2, 70, screenWidth_ / 2 - 10, screenHeight_ - 10);
    scrollArea_->setBackgroundRole(QPalette::Dark);
    scrollArea_->setWidgetResizable(true);
    scrollArea_->setWidget(buttonContainer_);

    refreshTimer_ = new QTimer(centralWidget());
    connect(refreshTimer_, &QTimer::timeout, this, &LobbyScreen::EnableRefreshButton);

    infoLabel_ = new QLabel();
    infoLabel_->setFont(QFont("Arial", 20));
    leftLayout_->addWidget(infoLabel_);

    cancelButton_ = new QPushButton("Delete room");
    leftLayout_->addWidget(cancelButton_);
    cancelButton_->hide();
    connect(cancelButton_, &QPushButton::pressed, this, &LobbyScreen::SendDelete);

    changeNicknameTimer_ = new QTimer(centralWidget());
    connect(changeNicknameTimer_, &QTimer::timeout, this, &LobbyScreen::EnableChangeNickname);

    changePasswordTimer_ = new QTimer(centralWidget());
    connect(changePasswordTimer_, &QTimer::timeout, this, &LobbyScreen::EnableChangePassword);
}

void LobbyScreen::SetGameScreen(ApplicationWindow* gameScreen) {
    gameScreen_ = gameScreen;
}

void LobbyScreen::AddLine() {
    auto line = new QFrame();
    line->setFrameShape(QFrame::HLine);

    if (leftLayout_) {
        leftLayout_->addWidget(line);
    }
}

void LobbyScreen::EnableRefreshButton() {
    refreshButton_->setEnabled(true);
}

void LobbyScreen::EnableChangeNickname() {
    if (newNickname_.isEmpty()) {
        changeNicknameButton_->setEnabled(true);
    }
}

void LobbyScreen::EnableChangePassword() {
    if (newPassword_.isEmpty()) {
        changePasswordButton_->setEnabled(true);
    }
}

void LobbyScreen::SetReadyToPlay(bool ready) {
    buttonContainer_->setEnabled(ready);
    createButton_->setEnabled(ready);
    changeNicknameButton_->setEnabled(ready);
    changePasswordButton_->setEnabled(ready);

    if (!ready) {
        infoLabel_->clear();
        roomToPlay_.clear();
    }
}

void LobbyScreen::ProcessMessage(const Query& query) {
    auto id = query.GetId();

    if (id == QueryId::RoomList) {
        ReceiveRoomList(query);
    }
    else if (id == QueryId::Join) {
        ReceiveJoinToRoom(query);
    }
    else if (id == QueryId::Accept) {
        ReceiveAccept(query);
    }
    else if (id == QueryId::AcceptResult) {
        ReceiveAcceptResult(query);
    }
    else if (id == QueryId::ChangeNickname) {
        ReceiveChangeNickname(query);
    }
}

void LobbyScreen::SendRoomList() {
    if (waitList_) {
        return;
    }

    refreshTimer_->start(5s);
    refreshButton_->setEnabled(false);
    socket_->Write(Query(QueryId::RoomList));
}

void LobbyScreen::ReceiveRoomList(const Query& query) {
    waitList_ = false;
    qDeleteAll(buttonContainer_->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));

    for (int i = 1; i < query.Size(); i += 3) {
        auto nickname = query.GetStringInfo(i);

        if (nickname == player_.GetNickname()) {
            continue;
        }

        auto rating = query.GetStringInfo(i + 1);
        auto isPrivate = query.GetIdInfo(i + 2) == QueryId::Private;
        auto button = new RoomButton(buttonContainer_, nickname, rating, isPrivate);
        connect(button, &QPushButton::clicked, this, &LobbyScreen::SendJoinToRoom);
        buttonLayout_->addWidget(button);
    }
}

void LobbyScreen::SendJoinToRoom() {
    Query query(QueryId::Join);
    auto pressedButton = reinterpret_cast<RoomButton*>(sender());
    SetReadyToPlay(true);
    roomToPlay_ = pressedButton->GetCreator();
    query.PushInfo(roomToPlay_);
    auto isPrivate = pressedButton->IsPrivate();

    if (isPrivate) {
        query.PushInfo(QInputDialog::getText(centralWidget(), "Password", "Type room password"));
    }

    socket_->Write(query);
    infoLabel_->setText("Connecting to server");
}

void LobbyScreen::ReceiveJoinToRoom(const Query& query) {
    if (query.GetIdInfo(1) == QueryId::Ok) {
        SendAccept();
    }
    else if (query.GetIdInfo(1) == QueryId::NotExist) {
        QMessageBox::critical(centralWidget(), "Error", "Game has started or room has deleted");
        SetReadyToPlay(false);
    }
}

void LobbyScreen::SendCreateRoom() {
    bool isPrivate;
    QString password;
    CreateRoomWindow dialog(this, isPrivate, password);
    dialog.exec();

    if (static_cast<QDialog::DialogCode>(dialog.result()) == QDialog::Accepted) {
        Query query(QueryId::Create);
        query.PushInfo(isPrivate ? QueryId::Private : QueryId::Public);

        if (isPrivate) {
            query.PushInfo(password);
        }

        socket_->Write(query);
        SetReadyToPlay(true);
        infoLabel_->setText("Waiting an enemy");
        roomToPlay_ = player_.GetNickname();
        cancelButton_->show();
    }
}

void LobbyScreen::SendAccept() {
    Query query(QueryId::Accept);
    auto answer = QueryId::Declined;

    QInputDialog dialog(this);
    dialog.setWindowTitle("Accepting");
    dialog.setTextValue("Are you ready for the game?");
    dialog.setOkButtonText("Accepted");
    dialog.setCancelButtonText("Declined");
    dialog.exec();

    if (static_cast<QDialog::DialogCode>(dialog.result()) == QDialog::Accepted) {
        answer = QueryId::Accepted;
    }
    else {
        SetReadyToPlay(false);
    }

    query.PushInfo(answer);
    socket_->Write(query);
}

void LobbyScreen::ReceiveAccept(const Query& query) {
    if (query.GetStringInfo(0) == roomToPlay_) {
        SendAccept();
    }
}

void LobbyScreen::SendDelete() {
    SetReadyToPlay(false);
    Query query(QueryId::Delete);
    socket_->Write(query);
}

void LobbyScreen::SendChangeNickname() {
    newNickname_ = QInputDialog::getText(centralWidget(), "Changing nickname", "Type new nickname");

    if (newNickname_ == player_.GetNickname()) {
        QMessageBox::critical(centralWidget(), "Changing nickname", "Nicknames must be different");
        newNickname_.clear();
        return;
    }

    if (newNickname_.size() < 3) {
        QMessageBox::critical(centralWidget(), "Changing nickname", "Nickname must contain at least 3 symbols");
        newNickname_.clear();
        return;
    }

    Query query(QueryId::ChangeNickname);
    query.PushInfo(newNickname_);
    socket_->Write(query);
}

void LobbyScreen::ReceiveChangeNickname(const Query& query) {
    if (query.GetIdInfo(0) == QueryId::Ok) {
        QMessageBox::information(centralWidget(), "Changing nickname", "Success");
        player_.SetNickname(newNickname_);
        nicknameLabel_->setText(newNickname_);
    }
    else if (query.GetIdInfo(0) == QueryId::AlreadyExist) {
        QMessageBox::critical(centralWidget(), "Changing nickname", "Nickname already exist");
    }

    newNickname_.clear();

    if (!changeNicknameTimer_->isActive()) {
        changeNicknameButton_->setEnabled(true);
    }
}

void LobbyScreen::SendChangePassword() {
    newPassword_ = QInputDialog::getText(centralWidget(), "Changing password", "Type new password");

    if (newPassword_.size() < 6) {
        QMessageBox::critical(centralWidget(), "Changing password", "Password must contain at least 6 symbols");
        newNickname_.clear();
        return;
    }

    Query query(QueryId::ChangePassword);
    query.PushInfo(newPassword_);
    socket_->Write(query);
}

void LobbyScreen::ReceiveChangePassword(const Query& query) {
    if (query.GetIdInfo(0) == QueryId::Ok) {
        QMessageBox::information(centralWidget(), "Changing password", "Success");
    }
    else if (query.GetIdInfo(0) == QueryId::Same) {
        QMessageBox::critical(centralWidget(), "Changing password", "Passwords are equal");
    }

    newPassword_.clear();

    if (!changePasswordTimer_->isActive()) {
        changePasswordButton_->setEnabled(true);
    }
}

void LobbyScreen::ReceiveAcceptResult(const Query& query) {
    if (query.GetIdInfo(0) == QueryId::Ok) {
        //Debug
        QMessageBox::information(centralWidget(), "Test", "Success");
        //
    }
    else if (query.GetIdInfo(0) == QueryId::Declined) {
        QMessageBox::critical(centralWidget(), "Notification", "Enemy declined game");
    }
}
