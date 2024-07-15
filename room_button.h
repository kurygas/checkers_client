#pragma once
#include <QPushButton>
#include <QString>

class RoomButton : public QPushButton {
public:
    RoomButton(QWidget* parent, const QString& creator, const QString& rating, bool isPrivate);

    [[nodiscard]] bool IsPrivate() const;
    [[nodiscard]] const QString& GetCreator() const;

private:
    QString roomCreator_;
    bool isPrivate_;
};