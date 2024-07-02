#pragma once
#include <QScreen>
#include <QApplication>
#include <QMainWindow>

class ApplicationWindow : public QMainWindow {
public:
    explicit ApplicationWindow();

protected:
    int screenWidth_;
};