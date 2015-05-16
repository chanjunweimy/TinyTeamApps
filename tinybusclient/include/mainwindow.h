#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cassert>

#include <QMainWindow>
#include <QString>
#include <QVBoxLayout>

#include "busservicepage.h"
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
    BusServicePage* _driverPage;
    BusBookingPage* _customerPage;
    QVBoxLayout* _windowLayout;
    QWidget* _windowWidget;

private slots:
    void handleLoginSuccess(QString role);
};

#endif // MAINWINDOW_H
