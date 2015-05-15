#ifndef BUSSERVICEPAGE_H
#define BUSSERVICEPAGE_H

#include QWidget;
#include QLineEdit;

class QWidget;
class QLineEdit;

class BusServicePage : public QWidget {
public:
    BusServicePage();
    ~BusServicePage();

private:
    setUpInputBusServiceBox();
    setUpSubmitButton();

private:
    QLineEdit _inputBox;
};

#endif // BUSSERVICEPAGE_H
