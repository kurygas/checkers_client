#include "create_room_window.h"

CreateRoomWindow::CreateRoomWindow(QWidget* parent, bool& isPrivate, QString& password)
: QDialog(parent)
, layout_(new QVBoxLayout(this))
, typeInput_(new QCheckBox("Private room", this))
, passwordInput_(new QLineEdit("Type a room password", this))
, isPrivate_(isPrivate)
, password_(password) {
    setWindowTitle("Room creation");
    layout_->addWidget(typeInput_);
    layout_->addWidget(passwordInput_);

    passwordInput_->setEnabled(false);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    layout_->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &CreateRoomWindow::CheckInput);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(typeInput_, &QCheckBox::stateChanged, this, &CreateRoomWindow::CheckBoxChanged);

    setWindowModality(Qt::WindowModal);
}

void CreateRoomWindow::CheckBoxChanged() {
    passwordInput_->setEnabled(typeInput_->checkState() == Qt::Checked);
}

void CreateRoomWindow::CheckInput() {
    isPrivate_ = typeInput_->checkState() == Qt::Checked;

    if (isPrivate_) {
        password_ = passwordInput_->text();

        if (password_.contains('$') || password_.contains('#')) {
            QMessageBox::critical(this, "Invalid password!", "Password must not contain symbols '$' and '#'");
            return;
        }
    }

    accept();
}
