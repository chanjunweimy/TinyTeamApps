#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    _windowWidget = new QWidget(this);

    _indexPage = new IndexPage(_windowWidget);
    _driverPage = new BusServicePage;
    _customerPage = new BusBookingPage(_windowWidget);

    _driverPage->hide();
    _customerPage->hide();

    _windowLayout = new QVBoxLayout;
    _windowLayout->addWidget(_indexPage);
    _windowLayout->addWidget(_driverPage);
    _windowLayout->addWidget(_customerPage);

    _windowWidget->setLayout(_windowLayout);
    this->setCentralWidget(_windowWidget);

    connect (_indexPage, SIGNAL(loginSuccessfully(QString)),
             this, SLOT(handleLoginSuccess(QString)));
}

MainWindow::~MainWindow() {
    delete _indexPage;
    delete _driverPage;
    delete _customerPage;
}

//private slots
void MainWindow::handleLoginSuccess(QString role) {
    _indexPage->hide();
    if (role == IndexPage::ROLE_DRIVER) {
        _driverPage->show();
    } else if (role == IndexPage::ROLE_CUSTOMER) {
        _customerPage->show();
    } else {
        assert (false);
    }
}
