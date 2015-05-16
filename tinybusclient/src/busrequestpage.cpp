#include "busrequestpage.h"

const int BusRequestPage::TABLE_COLUMN_NUMBER = 3;
const QString BusRequestPage::TICK_ICON_FILE = ":/image/local/tick.png";

BusRequestPage::BusRequestPage() {
    _widgetLayout = new QVBoxLayout();
    setUpTableWidget();
    setLayout(_widgetLayout);
}

BusRequestPage::~BusRequestPage() {
    delete _widgetLayout;
}

void BusRequestPage::setUpTableWidget() {
    QTableWidget *requestTable = new QTableWidget();

    QStringList tableHeader;
    tableHeader << "Bus Stop" << "Number of Requests" << "On Board";
    requestTable->setHorizontalHeaderLabels(tableHeader);

    QIcon tickIcon = QIcon (TICK_ICON_FILE);
    QString tickLabel = QString("YES");
    QTableWidgetItem *tickIconItem = new QTableWidgetItem(tickIcon, tickLabel);
    delete requestTable;
}
