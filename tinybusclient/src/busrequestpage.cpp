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

void BusRequestPage::buttonClicked() {
    this->hide();
    emit showBusServicePage();
}

void BusRequestPage::setUpTableWidget() {
    QTableWidget *requestTable = new QTableWidget(0, TABLE_COLUMN_NUMBER);

    QStringList tableHeader;
    tableHeader << "Bus\nStop" << "Number of\nRequests" << "On\nBoard";
    requestTable->setHorizontalHeaderLabels(tableHeader);
    requestTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _widgetLayout->addWidget(requestTable);

    requestTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    /*QHeaderView *verticalHeader = requestTable->verticalHeader();
    verticalHeader->sectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(200);*/

    QFont horizontalHeaderFont = requestTable->horizontalHeader()->font();
    horizontalHeaderFont.setBold(true);
    requestTable->horizontalHeader()->setFont(horizontalHeaderFont);

    int requestsSize = 1;
    for (int i = 0; i < requestsSize; i ++) {
        requestTable->insertRow(i);
        //column 1
        QTableWidgetItem *item = new QTableWidgetItem("12345\nbustop123 kjkg");
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled);
        requestTable->setItem(i, 0, item);
        //column 2
        item = new QTableWidgetItem("3");
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled);
        requestTable->setItem(i, 1, item);
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
        requestTable->setCellWidget(i, 2, tickWidget);
    }
    requestTable->resizeRowsToContents();
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

