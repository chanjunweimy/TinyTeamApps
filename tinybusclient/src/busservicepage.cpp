#include "busservicepage.h"

const QString BusServicePage::INPUT_BOX_LABEL = "Bus<br>Service<br>Number";
const QString BusServicePage::SUBMIT_BUTTON_LABEL = "Submit";
BusServicePage::BusServicePage(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    _widgetLayout = new QVBoxLayout();
    setBackgroundColor();
    setUpInputBox();
    setUpSubmitButton();
    setUpErrorLabel();
    this->setLayout(_widgetLayout);
}

BusServicePage::~BusServicePage() {
    delete _widgetLayout;
    delete _inputBox;
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


    JsonReader *jr = JsonReader::getObject();
    jr->loadBusServicesJson();
    QVector<BusStopObject> busServicesObjects = jr.getBusServicesObjects();
    QStringList busServiceList;
    for (int i = 0; i < busServicesObjects.size(); i ++) {
        busServiceList << busServicesObjects.at(i).getBusServices();
    }

    _inputBox = new QLineEdit();
    QFont inputBoxFont = _inputBox->font();
    inputBoxFont.setPointSize(20);
    _inputBox->setFont(inputBoxFont);
    _inputBox->setAlignment(Qt::AlignCenter);

    QCompleter *completer = new QCompleter(busServiceList);
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

    QWidget *dummyWidget = new QWidget();
    _widgetLayout->addWidget(dummyWidget, 10);
}

void BusServicePage::buttonClicked() {
    this->hide();
    QString busServiceNumber = _inputBox->text();
    emit busSelected(busServiceNumber);
}

void BusServicePage::setUpErrorLabel() {
    QLabel *errorLabel = new QLabel("Invalid bus service number");
    _widgetLayout->addWidget(errorLabel);
    QPalette palette = errorLabel->palette();
    palette.setColor(errorLabel->foregroundRole(), QColor(Qt::red));
    errorLabel->setPalette(palette);
    QFont labelFont = errorLabel->font();
    labelFont.setPointSize(20);
    errorLabel->setFont(labelFont);
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

