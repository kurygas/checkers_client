#pragma once
#include <QDialog>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>

class CreateRoomWindow : public QDialog {
public:
    CreateRoomWindow(QWidget* parent, bool& isPrivate, QString& password);

private:
    void CheckBoxChanged();
    void CheckInput();

    QVBoxLayout* layout_;
    QCheckBox* typeInput_;
    QLineEdit* passwordInput_;

    bool& isPrivate_;
    QString& password_;
};