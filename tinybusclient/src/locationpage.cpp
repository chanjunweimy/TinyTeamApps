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
    _busStopChosenLabel->setWordWrap(true);
    changeWidgetColorSettings(Qt::white,
                              Qt::red,
                              _busStopChosenLabel);

    QHBoxLayout* topWidgetLayout = new QHBoxLayout;
    topWidgetLayout->addWidget(busStopLabel, 0);
    topWidgetLayout->addWidget(_busStopChosenLabel, 1);

    _topWidget->setLayout(topWidgetLayout);

    _tableWidget = new QTableWidget(this);
    _tableWidget->setRowCount(0);
    _tableWidget->setColumnCount(1);
    _tableWidget->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);


    QStringList header;
    header << "Nearby Bus Stops";
    _tableWidget->setHorizontalHeaderLabels(header);

    _errorLabel = new QLabel(this);

    _confirmButton = new QPushButton(this);
    _confirmButton->setText("Confirm");

    QVBoxLayout *widgetLayout = new QVBoxLayout;
    widgetLayout->addWidget(_topWidget);
    widgetLayout->addWidget(_tableWidget);
    widgetLayout->addWidget(_errorLabel);
    widgetLayout->addWidget(_confirmButton);

    this->setLayout(widgetLayout);

    _topWidget->show();
    _tableWidget->show();
    _errorLabel->hide();
    _confirmButton->show();

    connect (_tableWidget, SIGNAL(cellClicked(int,int)),
             this, SLOT(handleCellClicked(int,int)));
    connect (_tableWidget, SIGNAL(cellPressed(int,int)),
             this, SLOT(handleCellClicked(int,int)));
    connect (_confirmButton, SIGNAL(clicked()),
             this, SLOT(handleButtonClicked()));

    updateBusStop();
}

LocationPage::~LocationPage() {
    delete _busStopChosenLabel;
    delete _tableWidget;
    delete _errorLabel;
    delete _topWidget;
    delete _confirmButton;
}

//public
bool LocationPage::updateBusStop() {
    if (!findNearbyBusStop()) {
        _topWidget->show();
        _tableWidget->show();
        _errorLabel->show();
        _confirmButton->show();
        return false;
    }
    _topWidget->show();
    _tableWidget->show();
    _errorLabel->hide();
    _confirmButton->show();
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
    if (!_objMap.isEmpty()) {
        _objMap.clear();
    }

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

            if (_busStopChosenLabel->text() == MSG_NO_BUS_STOP) {
                _busStopChosenLabel->setText(busStopNearBy);
            }

            QTableWidgetItem *newItem = new QTableWidgetItem(busStopNearBy);
            newItem->setText(busStopNearBy);
            newItem->setFlags(newItem->flags()
                              &= ~Qt::ItemIsEditable);
            _tableWidget->setItem(row, col, newItem);

            _objMap[busStopNearBy] = busStopObject;

            qDebug() << "LocationPage -> findNearbyBusStop: ";
            qDebug() << "row: " << row;
            qDebug() << "col: " << col;
            qDebug() << "text: " << newItem->text();
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
    QTableWidgetItem* item = _tableWidget->item(row, column);

    if (item == NULL) {
        return;
    }

    _busStopChosenLabel->setText(item->text());

    qDebug() << "LocationPage -> handleCellClicked: "
                "row: " << row;
    qDebug() << "column: " << column;
    qDebug() << "text: " << item->text();
}

void LocationPage::handleButtonClicked() {
    QString key = _busStopChosenLabel->text();
    BusStopObject obj = _objMap[key];
    emit this->busStopConfirmed(obj);
}
