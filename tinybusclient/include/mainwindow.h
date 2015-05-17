#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cassert>

#include <QMainWindow>
#include <QString>
#include <QVBoxLayout>
#include <QTimer>

#include "busservicepage.h"
#include "busrequestpage.h"
#include "busbookingpage.h"
#include "indexpage.h"

namespace Gui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    IndexPage* _indexPage;
    BusServicePage* _driverBusServicePage;
    BusRequestPage* _driverBusRequestPage;
    BusBookingPage* _customerPage;
    QVBoxLayout* _windowLayout;
    QWidget* _windowWidget;
    QTimer* _timer;

private slots:
    void handleLoginSuccess(QString role);
    void showBusRequestPage(QString busServiceNumber);
    void updateBusRequestPage();
};

#endif // MAINWINDOW_H
