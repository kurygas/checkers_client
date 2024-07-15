#include "room_button.h"

RoomButton::RoomButton(QWidget* parent, const QString& creator, const QString& rating, bool isPrivate)
: QPushButton(creator + '\t' + rating + '\t' + (isPrivate ? "Private" : "Public"), parent)
, roomCreator_(creator)
, isPrivate_(isPrivate) {}

const QString& RoomButton::GetCreator() const {
    return roomCreator_;
}

bool RoomButton::IsPrivate() const {
    return isPrivate_;
}
