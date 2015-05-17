#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    _windowWidget = new QWidget(this);

    _indexPage = new IndexPage(_windowWidget);
    _driverBusServicePage = new BusServicePage(_windowWidget);
    _driverBusRequestPage = new BusRequestPage(_windowWidget);
    _customerPage = new BusBookingPage(_windowWidget);

    _driverBusServicePage->hide();
    _driverBusRequestPage->hide();
    _customerPage->hide();

    _windowLayout = new QVBoxLayout;
    _windowLayout->addWidget(_indexPage);
    _windowLayout->addWidget(_driverBusServicePage);
    _windowLayout->addWidget(_driverBusRequestPage);
    _windowLayout->addWidget(_customerPage);

    connect(_driverBusServicePage, SIGNAL(busSelected(QString)),
            this, SLOT(showBusRequestPage(QString)));
    connect(_driverBusRequestPage, SIGNAL(showBusServicePage()),
            _driverBusServicePage, SLOT(show()));

    _windowWidget->setLayout(_windowLayout);
    this->setCentralWidget(_windowWidget);

    connect (_indexPage, SIGNAL(loginSuccessfully(QString)),
             this, SLOT(handleLoginSuccess(QString)));
}

MainWindow::~MainWindow() {
    delete _indexPage;
    delete _driverBusServicePage;
    delete _driverBusRequestPage;
    delete _customerPage;
}

//private slots
void MainWindow::handleLoginSuccess(QString role) {
    _indexPage->hide();
    if (role == IndexPage::ROLE_DRIVER) {
        _driverBusServicePage->show();
    } else if (role == IndexPage::ROLE_CUSTOMER) {
        _customerPage->show();
    } else {
        assert (false);
    }
}

void MainWindow::showBusRequestPage(QString busServiceNumber) {
    _driverBusRequestPage->setBusServiceNumber(busServiceNumber);
    _driverBusRequestPage->addContentToTable();
    _driverBusRequestPage->show();
}
