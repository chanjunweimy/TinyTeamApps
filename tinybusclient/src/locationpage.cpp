#include "locationpage.h"

const int LocationPage::OO = 1000;
const double LocationPage::RADIUS_EARTH = 6378137;//meter
const double LocationPage::MAX_DISTANCE = 400;//meter

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

//public
bool LocationPage::findNearbyBusStop() {
    double latitude = OO;
    double longitude = OO;
    if (!calculateCurrentGpsLocation(latitude, longitude)) {
        return false;
    }

    JsonReader *jr = JsonReader::getObject();
    QVector <BusStopObject> busStopObjects = jr->getBusStopObjects();

    for (int i = 0; i < busStopObjects.size(); i++) {
        BusStopObject busStopObject = busStopObjects[i];
        double latitude2 = busStopObject.getLatitude();
        double longitude2 = busStopObject.getLongtitude();

        double distance = calculateDistance(latitude, longitude,
                                            latitude2, longitude2);
    }
}

//private
double LocationPage::calculateDistance(double latitude1,
                                       double longitude1,
                                       double latitude2,
                                       double longitude2) {

    /**
     * dlon = lon2 - lon1
dlat = lat2 - lat1
a = (sin(dlat/2))^2 + cos(lat1) * cos(lat2) * (sin(dlon/2))^2
c = 2 * atan2( sqrt(a), sqrt(1-a) )
d = R * c (where R is the radius of the Earth)
     */
    double dlat = latitude2 - latitude1;
    double dlon = longitude2 - longitude1;

}

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
