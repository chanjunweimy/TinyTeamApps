#include "busservicepage.h"

const QString BusServicePage::INPUT_BOX_LABEL = "Bus<br>Service<br>Number";
const QString BusServicePage::SUBMIT_BUTTON_LABEL = "Submit";
BusServicePage::BusServicePage(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    _widgetLayout = new QVBoxLayout();
    setBackgroundColor();
    setUpInputBox();
    setUpSubmitButton();
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
    _widgetLayout->addWidget(dummyWidget, 10);

    QLabel *inputBoxLabel = new QLabel(INPUT_BOX_LABEL);
    QPalette palette = inputBoxLabel->palette();
    palette.setColor(inputBoxLabel->foregroundRole(), QColor(189, 215, 238));
    inputBoxLabel->setPalette(palette);
    QFont labelFont = inputBoxLabel->font();
    labelFont.setBold(true);
    labelFont.setPointSize(30);
    inputBoxLabel->setFont(labelFont);
    inputBoxLabel->setWordWrap(true);
    inputBoxLabel->setAlignment(Qt::AlignCenter);
    _widgetLayout->addWidget(inputBoxLabel);


    JsonReader *jr = JsonReader::getObject();
    //QVector<BusStopObject> busServicesObjects = jr.getBusServicesObjects();
    QStringList busServiceList;
    busServiceList << "95" << "96";

    _inputBox = new QLineEdit();
    QFont inputBoxFont = _inputBox->font();
    inputBoxFont.setPointSize(20);
    _inputBox->setFont(inputBoxFont);
    _inputBox->setAlignment(Qt::AlignCenter);

    QCompleter *completer = new QCompleter(busServiceList);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    _inputBox->setCompleter(completer);
    _widgetLayout->addWidget(_inputBox);
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

void BusServicePage::setButtonStyleSheet(QPushButton *button) {
    button->setStyleSheet("background-color: rgb(46, 117, 182);"
                          "border-radius: 7px;"
                          "font: 20px;"
                          "color: white;"
                          "padding: 6px;"
                          "margin: 6px;");
    button->setCursor(Qt::PointingHandCursor);
}

