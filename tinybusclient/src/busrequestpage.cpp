#include "busrequestpage.h"

const int BusRequestPage::TABLE_COLUMN_NUMBER = 3;
const QString BusRequestPage::TICK_ICON_FILE = ":/image/local/tick.png";
const QString BusRequestPage::END_BUTTON_LABEL = "End of Journey";

BusRequestPage::BusRequestPage(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    _widgetLayout = new QVBoxLayout();
    setBackgroundColor();
    setUpTableWidget();
    setUpEndButton();
    this->setLayout(_widgetLayout);
}

BusRequestPage::~BusRequestPage() {
    delete _widgetLayout;
}

void BusRequestPage::setBackgroundColor() {
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor(64, 64, 64));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

void BusRequestPage::setBusServiceNumber(QString busServiceNumber) {
    _busServiceNumber = busServiceNumber;
}

void BusRequestPage::setUpEndButton() {
    QPushButton *endButton = new QPushButton(END_BUTTON_LABEL);

    setButtonStyleSheet(endButton);
    connect(endButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    _widgetLayout->addWidget(endButton);

    QWidget *dummyWidget = new QWidget();
    _widgetLayout->addWidget(dummyWidget, 10);
}

void BusRequestPage::buttonClicked() {
    this->hide();
    emit showBusServicePage();
}

void BusRequestPage::setUpTableWidget() {
    QTableWidget *requestTable = new QTableWidget(2, TABLE_COLUMN_NUMBER);

    QStringList tableHeader;
    tableHeader << "Bus Stop" << "Number of Requests" << "On Board";
    requestTable->setHorizontalHeaderLabels(tableHeader);
    _widgetLayout->addWidget(requestTable);

    QIcon tickIcon = QIcon (TICK_ICON_FILE);
    QString tickLabel = QString("YES");
    QTableWidgetItem *tickIconItem = new QTableWidgetItem(tickIcon, tickLabel);
}

void BusRequestPage::setButtonStyleSheet(QPushButton *button) {
    button->setStyleSheet("background-color: rgb(159, 33, 33);"
                          "border-radius: 7px;"
                          "font: 20px;"
                          "color: white;"
                          "padding: 6px;"
                          "margin: 6px;");
    button->setCursor(Qt::PointingHandCursor);
}

