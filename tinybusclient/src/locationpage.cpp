#include "locationpage.h"

const int LocationPage::OO = 1000;

LocationPage::LocationPage(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f) {

    //initialize
    QWidget* topWidget = new QWidget(this);
    QLabel* busStopLabel = new QLabel(topWidget);
    busStopLabel->setText("Bus Stop: ");
    changeWidgetColorSettings(Qt::white,
                              Qt::black,
                              busStopLabel);

    _busStopChosenLabel = new QLabel(topWidget);
    changeWidgetColorSettings(Qt::white,
                              Qt::red,
                              _busStopChosenLabel);

    QHBoxLayout* topWidgetLayout = new QHBoxLayout;
    topWidgetLayout->addWidget(busStopLabel);
    topWidgetLayout->addWidget(_busStopChosenLabel);

    topWidget->setLayout(topWidgetLayout);

    _tableWidget = new QTableWidget(this);
    _tableWidget->setRowCount(0);
    _tableWidget->setColumnCount(1);

    QStringList header;
    header << "Nearby Bus Stops";
    _tableWidget->setHorizontalHeaderLabels(header);

    _errorLabel = new QLabel(this);

    QVBoxLayout *widgetLayout = new QVBoxLayout;
    widgetLayout->addWidget(topWidget);
    widgetLayout->addWidget(_tableWidget);
    widgetLayout->addWidget(_errorLabel);

    this->setLayout(widgetLayout);

    topWidget->show();
    _tableWidget->show();
    _errorLabel->hide();



}

LocationPage::~LocationPage() {
    delete _busStopChosenLabel;
    delete _tableWidget;
    delete _errorLabel;
}

//private
void LocationPage::changeWidgetColorSettings(QColor background,
                                             QColor font,
                                             QWidget *widget) {
    widget->setAutoFillBackground(true);
    QPalette pallete = widget->palette();
    pallete.setColor(widget->backgroundRole(), background);
    pallete.setColor(widget->foregroundRole(), font);
    widget->setPalette(pallete);
}

bool LocationPage::calculateCurrentGpsLocation(double &latitude,
                                               double &longitude) {
    latitude = 1.300000;
    longitude = 104.000000;
    return true;
}
