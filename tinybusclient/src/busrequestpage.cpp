#include "busrequestpage.h"

const int BusRequestPage::TABLE_COLUMN_NUMBER = 3;
const QString BusRequestPage::TICK_ICON_FILE = ":/image/local/tick.png";
const QString BusRequestPage::END_BUTTON_LABEL = "End of Journey";

BusRequestPage::BusRequestPage(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    _widgetLayout = new QVBoxLayout();
    setBackgroundColor();
    setUpBusServiceLabel();
    setUpTableWidget();
    setUpEndButton();
    this->setLayout(_widgetLayout);
}

BusRequestPage::~BusRequestPage() {
    delete _widgetLayout;
    delete _requestTable;
    delete _busServiceLabel;
    delete _tickButtonGroup;
}

void BusRequestPage::setUpBusServiceLabel() {
    _busServiceLabel = new QLabel(_busServiceNumber);
    QPalette palette = _busServiceLabel->palette();
    palette.setColor(_busServiceLabel->foregroundRole(), QColor(189, 215, 238));
    _busServiceLabel->setPalette(palette);
    QFont labelFont = _busServiceLabel->font();
    labelFont.setBold(true);
    labelFont.setPointSize(40);
    _busServiceLabel->setFont(labelFont);
    _busServiceLabel->setAlignment(Qt::AlignCenter);
    _busServiceLabel->setMaximumHeight(_busServiceLabel->sizeHint().height());
    _widgetLayout->addWidget(_busServiceLabel);
}

void BusRequestPage::setBackgroundColor() {
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor(64, 64, 64));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

void BusRequestPage::setBusServiceNumber(QString busServiceNumber) {
    _busServiceNumber = busServiceNumber;
    _busServiceLabel->setText(_busServiceNumber);
}

void BusRequestPage::setUpEndButton() {
    QPushButton *endButton = new QPushButton(END_BUTTON_LABEL);

    setButtonStyleSheet(endButton);
    connect(endButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    _widgetLayout->addWidget(endButton);

    QWidget *dummyWidget = new QWidget();
    _widgetLayout->addWidget(dummyWidget);
}

void BusRequestPage::setUpTableWidget() {
    _requestTable = new QTableWidget(0, TABLE_COLUMN_NUMBER);

    QStringList tableHeader;
    tableHeader << "Bus\nStop" << "Number of\nRequests" << "On\nBoard";
    _requestTable->setHorizontalHeaderLabels(tableHeader);
    _widgetLayout->addWidget(_requestTable);

    _requestTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _requestTable->verticalHeader()->hide();

    QFont horizontalHeaderFont = _requestTable->horizontalHeader()->font();
    horizontalHeaderFont.setBold(true);
    _requestTable->horizontalHeader()->setFont(horizontalHeaderFont);
}

void BusRequestPage::setButtonStyleSheet(QPushButton *button) {
    button->setStyleSheet("background-color: rgb(159, 33, 33);"
                          "border-radius: 7px;"
                          "font: 60px;"
                          "color: white;"
                          "padding: 6px;"
                          "margin: 6px;");
    button->setCursor(Qt::PointingHandCursor);
}

void BusRequestPage::resizeTable()
{
    int sumOfRowHeight = _requestTable->horizontalHeader()->height();
    for (int i = 0; i < _requestTable->rowCount(); i ++) {
        sumOfRowHeight += _requestTable->rowHeight(i);
    }
    _requestTable->setMinimumHeight(sumOfRowHeight);
    _requestTable->setMaximumHeight(sumOfRowHeight);
}

void BusRequestPage::addContentToTable() {
    while (_requestTable->rowCount() > 0)
    {
        _requestTable->removeRow(0);
    }

    JsonReader *jr = JsonReader::getObject();
    jr->loadBusRequestsJson();
    QVector<BusRequestObject> busRequestObjects = jr->getBusRequestObjects();
    int requestsSize = busRequestObjects.size();
    for (int i = requestsSize - 1; i >= 0; i --) {
        BusRequestObject curBusRequest = busRequestObjects.value(i);
        QString busNumber = curBusRequest.getBusServiceNumber();
        while (busNumber.at(0) == '0') {
            busNumber = busNumber.mid(1);
        }

        if (busNumber != _busServiceNumber) {
            busRequestObjects.removeAt(i);
        }
    }

    _numberOfRequestItems = QVector<QTableWidgetItem*>();
    _tickButtonGroup = new QButtonGroup();
    requestsSize = busRequestObjects.size();
    for (int i = 0; i < requestsSize; i ++) {
        _requestTable->insertRow(i);
        BusRequestObject curBusRequest = busRequestObjects.value(i);
        //column 1
        QString busStopString = curBusRequest.getBusStopNumber() + "\n" +
                                curBusRequest.getBusStopName();
        QTableWidgetItem *item = new QTableWidgetItem(busStopString);
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled);
        _requestTable->setItem(i, 0, item);

        //column 2
        item = new QTableWidgetItem(QString::number(curBusRequest.getNumberOfRequest()));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled);
        _requestTable->setItem(i, 1, item);
        _numberOfRequestItems.append(item);

        //column 3
        QWidget* tickWidget = new QWidget();
        QPushButton* tickButton = new QPushButton();
        QPixmap pixmap(TICK_ICON_FILE);
        QIcon ButtonIcon(pixmap);
        tickButton->setIcon(ButtonIcon);
        tickButton->setIconSize(pixmap.rect().size());
        QHBoxLayout* tickLayout = new QHBoxLayout(tickWidget);
        tickLayout->addWidget(tickButton);
        tickLayout->setAlignment(Qt::AlignCenter);
        tickLayout->setContentsMargins(0, 0, 0, 0);
        tickWidget->setLayout(tickLayout);
        _requestTable->setCellWidget(i, 2, tickWidget);
        _tickButtonGroup->addButton(tickButton, i);
    }
    _requestTable->resizeRowsToContents();

    resizeTable();

    connect(_tickButtonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(updateNumberOfRequest(int)));
}

//private slots
void BusRequestPage::buttonClicked() {
    this->hide();
    emit showBusServicePage();
}

void BusRequestPage::updateNumberOfRequest(int rowNumber) {
    int numberOfRequest = _numberOfRequestItems.value(rowNumber)->text().toInt();
    numberOfRequest--;
    if (numberOfRequest == 0) {
        _requestTable->setRowHidden(rowNumber, true);
        resizeTable();
    } else {
        _numberOfRequestItems.value(rowNumber)->setText(QString::number(numberOfRequest));
    }
}
