#include "busservicepage.h"

const QString BusServicePage::INPUT_BOX_LABEL = "Bus<br>Service<br>Number";
const QString BusServicePage::SUBMIT_BUTTON_LABEL = "Submit";
BusServicePage::BusServicePage(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    initializeWidget();
}

BusServicePage::~BusServicePage() {
    delete _widgetLayout;
    delete _inputBox;
}

void BusServicePage::initializeWidget() {
    _widgetLayout = new QVBoxLayout();
    initializeBusServiceList();
    setBackgroundColor();
    setUpInputBox();
    setUpSubmitButton();
    setUpErrorLabel();
    this->setLayout(_widgetLayout);
}

void BusServicePage::initializeBusServiceList() {
    JsonReader *jr = JsonReader::getObject();
    jr->loadBusServicesJson();
    QVector<BusServicesObject> busServiceObjects = jr->getBusServiceObjects();
    for (int i = 0; i < busServiceObjects.size(); i ++) {
        QString busNumber = busServiceObjects.value(i).getBusNumber();
        while (busNumber.at(0) == '0') {
            busNumber = busNumber.mid(1);
        }
        _busServiceList.append(busNumber);
    }
}

void BusServicePage::setBackgroundColor() {
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor(64, 64, 64));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

void BusServicePage::setUpInputBox() {
    QWidget *dummyWidget = new QWidget();
    _widgetLayout->addWidget(dummyWidget, 1);

    QLabel *inputBoxLabel = new QLabel(INPUT_BOX_LABEL);
    QPalette palette = inputBoxLabel->palette();
    palette.setColor(inputBoxLabel->foregroundRole(), QColor(189, 215, 238));
    inputBoxLabel->setPalette(palette);
    QFont labelFont = inputBoxLabel->font();
    labelFont.setBold(true);
    labelFont.setPointSize(40);
    inputBoxLabel->setFont(labelFont);
    inputBoxLabel->setAlignment(Qt::AlignCenter);
    _widgetLayout->addWidget(inputBoxLabel);

    _widgetLayout->addWidget(dummyWidget, 1);

    _inputBox = new QLineEdit();
    QFont inputBoxFont = _inputBox->font();
    inputBoxFont.setPointSize(20);
    _inputBox->setFont(inputBoxFont);
    _inputBox->setAlignment(Qt::AlignCenter);
    _inputBox->setMaxLength(4);
    _inputBox->setPlaceholderText("Please input bus service number");

    connect(_inputBox, SIGNAL(returnPressed()),
            this, SLOT(buttonClicked()));

    QCompleter *completer = new QCompleter(_busServiceList);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    _inputBox->setCompleter(completer);
    _widgetLayout->addWidget(_inputBox);
    _widgetLayout->addWidget(dummyWidget, 1);
}

void BusServicePage::setUpSubmitButton() {
    QPushButton *submitButton = new QPushButton(SUBMIT_BUTTON_LABEL);
    setButtonStyleSheet(submitButton);
    connect(submitButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    _widgetLayout->addWidget(submitButton);
}

void BusServicePage::buttonClicked() {
    QString busServiceNumber = _inputBox->text().trimmed();
    if (_busServiceList.contains(busServiceNumber)) {
        _errorLabel->hide();
        this->hide();
        emit busSelected(busServiceNumber);
    } else {
        _errorLabel->show();
    }
}

void BusServicePage::setUpErrorLabel() {
    _errorLabel = new QLabel("Invalid bus service number");
    QPalette palette = _errorLabel->palette();
    palette.setColor(_errorLabel->foregroundRole(), QColor(Qt::red));
    _errorLabel->setPalette(palette);
    QFont labelFont = _errorLabel->font();
    labelFont.setPointSize(20);
    _errorLabel->setFont(labelFont);
    _errorLabel->hide();
    _widgetLayout->addWidget(_errorLabel);

    QWidget *dummyWidget = new QWidget();
    _widgetLayout->addWidget(dummyWidget, 10);
}

void BusServicePage::setButtonStyleSheet(QPushButton *button) {
    button->setStyleSheet("background-color: rgb(46, 117, 182);"
                          "border-radius: 7px;"
                          "font: 60px;"
                          "color: white;"
                          "padding: 6px;"
                          "margin: 6px;");
    button->setCursor(Qt::PointingHandCursor);
}

