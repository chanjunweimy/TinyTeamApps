#include "busrequestpage.h"

const int BusRequestPage::TABLE_COLUMN_NUMBER = 3;

BusRequestPage::BusRequestPage() {
    setUpTableWidget();
    _widgetLayout = new QVBoxLayout();
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

    //QTableWidgetItem *tableItem = new QTableWidgetItem("");
    delete requestTable;
}
