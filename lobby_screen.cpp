#include "lobby_screen.h"

LobbyScreen::LobbyScreen(Socket* socket, PlayerInfo& player, ApplicationWindow* loginScreen)
: ApplicationWindow(socket, player)
, loginScreen_(loginScreen) {}

void LobbyScreen::Draw() {
    nicknameLabel_ = new QLabel(centralWidget());
    nicknameLabel_->setGeometry(10, 10, screenWidth_ / 2 - 10, 50);
    nicknameLabel_->setFont(QFont("Arial", 20));
    nicknameLabel_->setText(player_.GetNickname());

    ratingLabel_ = new QLabel(centralWidget());
    ratingLabel_->setGeometry(10, 70, screenWidth_ / 2 - 10, 50);
    ratingLabel_->setFont(QFont("Arial", 20));
    ratingLabel_->setText("Rating: " + QString::number(player_.GetRating()));

    createButton_ = new QPushButton(centralWidget());
    createButton_->setGeometry(screenWidth_ / 2, 10, screenWidth_ / 4 - 5, 50);
    createButton_->setText("Create new room");
    connect(createButton_, &QPushButton::pressed, this, &LobbyScreen::SendCreateRoom);

    refreshButton_ = new QPushButton(centralWidget());
    refreshButton_->setGeometry(screenWidth_ / 4 * 3 - 5, 10, screenWidth_ / 4 - 5, 50);
    refreshButton_->setText("Refresh room list");
    connect(refreshButton_, &QPushButton::pressed, this, &LobbyScreen::SendRoomList);

    buttonBox_ = new QDialogButtonBox(Qt::Vertical);

    auto scrollArea_ = new QScrollArea(centralWidget());
    scrollArea_->setGeometry(screenWidth_ / 2, 70, screenWidth_ / 2 - 10, screenHeight_ - 90);
    scrollArea_->setBackgroundRole(QPalette::Dark);
    scrollArea_->setWidget(buttonBox_);

    refreshTimer_ = new QTimer(centralWidget());
    connect(refreshTimer_, &QTimer::timeout, this, &LobbyScreen::EnableRefreshButton);
}

void LobbyScreen::SetGameScreen(ApplicationWindow* gameScreen) {
    gameScreen_ = gameScreen;
}

void LobbyScreen::ProcessMessage(const QList<QString>& message) {
    if (message.front() == "room list") {
        ReceiveRoomList(message);
    }
}

void LobbyScreen::EnableRefreshButton() {
    refreshButton_->setEnabled(true);
}

void LobbyScreen::SendRoomList() {
    if (!refreshTimer_->isActive()) {
        refreshTimer_->start(5s);
        refreshButton_->setEnabled(false);
        socket_->Write({"room list"});
    }
}

void LobbyScreen::ReceiveRoomList(const QList<QString>& message) {
    buttonBox_->clear();

    for (int i = 1; i < message.size(); i += 3) {
        QList<QString> buttonInfo;

        for (int j = 0; j < 3; ++j) {
            buttonInfo.push_back(message[i + j]);
        }

        auto button = new QPushButton(buttonInfo.join('\n'));
        buttonBox_->addButton(button, QDialogButtonBox::ActionRole);
    }
}

void LobbyScreen::SendJoinToRoom() {
    auto pressedButton = reinterpret_cast<QPushButton*>(sender());
    buttonBox_->setEnabled(false);
    auto creatorName = pressedButton->text().split('\n').front();
    socket_->Write({"join", creatorName});
}

void LobbyScreen::ReceiveJoinToRoom(const QList<QString>& message) {

}

void LobbyScreen::SendCreateRoom() {

}

void LobbyScreen::ReceiveCreateRoom(const QList<QString>& message) {

}
