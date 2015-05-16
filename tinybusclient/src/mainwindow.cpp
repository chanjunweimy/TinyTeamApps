#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    _indexPage = new IndexPage(this);
    _driverPage = new BusServicePage;
    _customerPage = new BusBookingPage(this);

    _driverPage->hide();
    _customerPage->hide();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(_indexPage);
    layout->addWidget(_driverPage);
    layout->addWidget(_customerPage);

    this->setLayout(layout);

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
    if (role == IndexPage::ROLE_DRIVER) {
        _driverPage->show();
    } else if (role == IndexPage::ROLE_CUSTOMER) {
        _customerPage->show();
    } else {
        assert (false);
    }
}
