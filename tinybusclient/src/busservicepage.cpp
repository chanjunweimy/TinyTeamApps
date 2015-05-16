#include "busservicepage.h"

const QString BusServicePage::INPUT_BOX_LABEL = "Bus Service Number: ";
const QString BusServicePage::SUBMIT_BUTTON_LABEL = "Submit";
BusServicePage::BusServicePage() {
    setUpInputBox();
    setUpSubmitButton();
    _widgetLayout = new QVBoxLayout();
    setLayout(_widgetLayout);
}

BusServicePage::~BusServicePage() {

}

void BusServicePage::setUpInputBox() {
    QLabel *inputBoxLabel = new QLabel(INPUT_BOX_LABEL);
    _widgetLayout->addWidget(inputBoxLabel);

    QStringList busServiceList;
    busServiceList << "95" << "96";

    _inputBox = new QLineEdit();
    QCompleter *completer = new QCompleter(busServiceList);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    _inputBox->setCompleter(completer);

    _widgetLayout->addWidget(_inputBox);

    delete inputBoxLabel;
}

void BusServicePage::setUpSubmitButton() {
    QPushButton *submitButton = new QPushButton(SUBMIT_BUTTON_LABEL);
    connect(submitButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    _widgetLayout->addWidget(submitButton);

    delete submitButton;
}

void BusServicePage::buttonClicked() {
    QString busServiceNumber = _inputBox->text();
    emit selectedBus(busServiceNumber);
}


