#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    _windowLayout = new QVBoxLayout();
    setupWindows();
    setupWidget();
}

void MainWindow::setupWidget() {
    _windowWidget->setAutoFillBackground(true);
    QPalette pallete = _windowWidget->palette();
    pallete.setColor(_windowWidget->backgroundRole(), Qt::white);
    _windowWidget->setPalette(pallete);

    _windowWidget->setLayout(_windowLayout);

    _windowWidget->setMaximumHeight(_clientHeight);
    _windowWidget->setMaximumWidth(_clientWidth);
    this->setCentralWidget(_windowWidget);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void MainWindow::setupWindows() {
    QDesktopWidget widget;
    QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());

    _clientHeight = mainScreenSize.height();
    _clientWidth = mainScreenSize.width();

    this->resize(_clientWidth, _clientHeight);

    int posX = 0;
    int posY = 0;
    this->move(posX, posY);
}

MainWindow::~MainWindow() {
}
