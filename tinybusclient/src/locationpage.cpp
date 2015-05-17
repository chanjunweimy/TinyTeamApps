#include "locationpage.h"

const int LocationPage::OO = 1000;
const double LocationPage::RADIUS_EARTH = 6378137;//meter
const double LocationPage::MAX_DISTANCE = 400;//meter
const double LocationPage::PI = 3.145926535;
const double LocationPage::DEGREE_180 = 180;
const QString LocationPage::MSG_NO_BUS_STOP = "No Bus Stop NearBy";

LocationPage::LocationPage(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f) {

    //initialize
    _topWidget = new QWidget(this);
    QLabel* busStopLabel = new QLabel(_topWidget);
    busStopLabel->setText("Bus Stop: ");
    changeWidgetColorSettings(Qt::white,
                              Qt::black,
                              busStopLabel);

    _busStopChosenLabel = new QLabel(_topWidget);
    _busStopChosenLabel->setText(MSG_NO_BUS_STOP);
    changeWidgetColorSettings(Qt::white,
                              Qt::red,
                              _busStopChosenLabel);

    QHBoxLayout* topWidgetLayout = new QHBoxLayout;
    topWidgetLayout->addWidget(busStopLabel);
    topWidgetLayout->addWidget(_busStopChosenLabel);

    _topWidget->setLayout(topWidgetLayout);

    _tableWidget = new QTableWidget(this);
    _tableWidget->setRowCount(0);
    _tableWidget->setColumnCount(1);

    QStringList header;
    header << "Nearby Bus Stops";
    _tableWidget->setHorizontalHeaderLabels(header);

    _errorLabel = new QLabel(this);

    QVBoxLayout *widgetLayout = new QVBoxLayout;
    widgetLayout->addWidget(_topWidget);
    widgetLayout->addWidget(_tableWidget);
    widgetLayout->addWidget(_errorLabel);

    this->setLayout(widgetLayout);

    _topWidget->show();
    _tableWidget->show();
    _errorLabel->hide();

    connect (_tableWidget, SIGNAL(cellClicked(int,int)),
             this, SLOT(handleCellClicked(int,int)));
    connect (_tableWidget, SIGNAL(cellPressed(int,int)),
             this, SLOT(handleCellClicked(int,int)));

    updateBusStop();
}

LocationPage::~LocationPage() {
    delete _busStopChosenLabel;
    delete _tableWidget;
    delete _errorLabel;
    delete _topWidget;
}

//public
bool LocationPage::updateBusStop() {
    if (!findNearbyBusStop()) {
        _topWidget->hide();
        _tableWidget->hide();
        _errorLabel->show();
        return false;
    }
    _topWidget->show();
    _tableWidget->show();
    _errorLabel->hide();
    return true;
}

//private
bool LocationPage::findNearbyBusStop() {
    double latitude = OO;
    double longitude = OO;
    if (!calculateCurrentGpsLocation(latitude, longitude)) {
        QString errorMsg = "gps not working";
        qDebug() << "LocationPage -> findNearbyBusStop: "
                 << errorMsg;
        _errorLabel->setText(errorMsg);
        return false;
    }

    JsonReader *jr = JsonReader::getObject();
    if (!jr->loadBusStopsJson()) {
        QString errorMsg = "busstops.json is not loaded";
        qDebug() << "LocationPage -> findNearbyBusStop: "
                 << errorMsg;
        _errorLabel->setText(errorMsg);
        return false;
    }
    QVector <BusStopObject> busStopObjects = jr->getBusStopObjects();

    _tableWidget->clearContents();
    for (int i = 0; i < busStopObjects.size(); i++) {
        BusStopObject busStopObject = busStopObjects[i];
        double latitude2 = busStopObject.getLatitude();
        double longitude2 = busStopObject.getLongtitude();

        double distance = calculateDistance(latitude, longitude,
                                            latitude2, longitude2);
        qDebug() << "LocationPage -> findNearbyBusStop: "
                    "BusStopNumber: "
                 << busStopObject.getBusStopNumber();
        qDebug() << "BusStopDescription: "
                 << busStopObject.getBusStopDescription();
        qDebug() << "DistanceOfBusStopToHere: "
                 << distance;

        if (distance <= MAX_DISTANCE) {
            QString busStopNearBy = busStopObject.getBusStopNumber() +
                    " " +
                    busStopObject.getBusStopDescription();
            int row = _tableWidget->rowCount();
            int col = _tableWidget->columnCount() - 1;
            _tableWidget->insertRow(row);

            QTableWidgetItem *newItem = new QTableWidgetItem(busStopNearBy);
            _tableWidget->setItem(row, col, newItem);
        }
    }


    return true;
}

double LocationPage::calculateDistance(double latitude1,
                                       double longitude1,
                                       double latitude2,
                                       double longitude2) {
    latitude1 = toRadiant(latitude1);
    longitude1 = toRadiant(longitude1);
    latitude2 = toRadiant(latitude2);
    longitude2 = toRadiant(longitude2);


    /**
     * dlon = lon2 - lon1
dlat = lat2 - lat1
a = (sin(dlat/2))^2 + cos(lat1) * cos(lat2) * (sin(dlon/2))^2
c = 2 * atan2( sqrt(a), sqrt(1-a) )
d = R * c (where R is the radius of the Earth)
     */
    double dlat = latitude2 - latitude1;
    double dlon = longitude2 - longitude1;

    double sinDlatSquare = sin (dlat/2);
    sinDlatSquare *= sinDlatSquare;

    double sinDlonSquare = sin (dlon/2);
    sinDlonSquare *= sinDlonSquare;

    double a = sinDlatSquare + cos(latitude1)
            * cos(latitude2) * sinDlonSquare;
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = RADIUS_EARTH * c;

    return distance;
}

double LocationPage::toRadiant(double degree) {
    double rad = degree * PI / DEGREE_180;
    return rad;
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
    latitude = 1.295339;
    longitude = 103.851143;
    return true;
}

//private slots
void LocationPage::handleCellClicked(int row, int column) {
    QTableWidgetItem* item = _tableWidget->itemAt(row, column);
    _busStopChosenLabel->setText(item->text());
}
