#include "busservicepage.h"

BusServicePage::BusServicePage() {
    setUpInputBox();
    setUpSubmitButton();
    _widgetLayout = new QVBoxLayout();
    setLayout(_widgetLayout);
}

BusServicePage::~BusServicePage() {

}

void BusServicePage::setUpInputBox() {
    QLabel *inputBoxLabel = new QLabel("Bus Service Number: ");
    _widgetLayout->addWidget(inputBoxLabel);

    _inputBox = new QLineEdit();
    _widgetLayout->addWidget(_inputBox);

    delete inputBoxLabel;
}

void BusServicePage::setUpSubmitButton() {
    QPushButton *submitButton = new QPushButton("Submit");

    connect(submitButton, SIGNAL(clicked()), this, buttonClicked());

    _widgetLayout->addWidget(submitButton);

    delete submitButton;
}

void BusServicePage::buttonClicked() {

}


