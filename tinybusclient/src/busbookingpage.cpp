#include "busbookingpage.h"

const int BusBookingPage::OO = 1000;
const double BusBookingPage::RADIUS_EARTH = 6378137;//meter
const double BusBookingPage::MAX_DISTANCE = 400;//meter
const double BusBookingPage::PI = 3.145926535;
const double BusBookingPage::DEGREE_180 = 180;
const QString BusBookingPage::MSG_NO_BUS_STOP = "No Bus Stop NearBy";
const QString BusBookingPage::MSG_NO_BUS = "No Bus Is Chosen";

BusBookingPage::BusBookingPage(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f) {

    //initialize
    _headerLabel = new QLabel(this);
    changeWidgetColorSettings(Qt::darkGreen,
                              Qt::white,
                              _headerLabel);

    _headerLabel->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Maximum);
    _headerLabel->setText("Bus Stop");
    _headerLabel->setAlignment(Qt::AlignCenter);
    QFont font = _headerLabel->font();
    font.setPointSize(18);
    font.setBold(true);
    _headerLabel->setFont(font);


    _busStopWidget = new QWidget(this);
    _busStopLabel = new QLabel(_busStopWidget);
    _busStopLabel->setText("Bus Stop: ");
    changeWidgetColorSettings(Qt::white,
                              Qt::black,
                              _busStopLabel);

    _busStopChosenLabel = new QLabel(_busStopWidget);
    _busStopChosenLabel->setText(MSG_NO_BUS_STOP);
    _busStopChosenLabel->setWordWrap(true);
    changeWidgetColorSettings(Qt::white,
                              Qt::red,
                              _busStopChosenLabel);

    QHBoxLayout* busStopLayout = new QHBoxLayout;
    busStopLayout->addWidget(_busStopLabel, 0);
    busStopLayout->addWidget(_busStopChosenLabel, 1);

    _busStopWidget->setLayout(busStopLayout);


    _busWidget = new QWidget(this);
    _busLabel = new QLabel(_busWidget);
    _busLabel->setText("Bus Stop: ");
    changeWidgetColorSettings(Qt::white,
                              Qt::black,
                              _busLabel);

    _busChosenLabel = new QLabel(_busWidget);
    _busChosenLabel->setText(MSG_NO_BUS);
    _busChosenLabel->setWordWrap(true);
    changeWidgetColorSettings(Qt::white,
                              Qt::red,
                              _busChosenLabel);

    QHBoxLayout* busLayout = new QHBoxLayout;
    busLayout->addWidget(_busLabel, 0);
    busLayout->addWidget(_busChosenLabel, 1);

    _busWidget->setLayout(busLayout);


    _tableWidget = new QTableWidget(this);
    _tableWidget->setRowCount(0);
    _tableWidget->setColumnCount(1);

    QStringList header;
    header << "Nearby Bus Stops";
    _tableWidget->setHorizontalHeaderLabels(header);

    _tableWidget->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);

    _errorLabel = new QLabel(this);

    _confirmButton = new QPushButton(this);
    _confirmButton->setText("Confirm");

    QVBoxLayout *widgetLayout = new QVBoxLayout;
    widgetLayout->addWidget(_headerLabel);
    widgetLayout->addWidget(_busStopWidget);
    widgetLayout->addWidget(_busWidget);
    widgetLayout->addWidget(_tableWidget);
    widgetLayout->addWidget(_errorLabel);
    widgetLayout->addWidget(_confirmButton);

    this->setLayout(widgetLayout);

    changeWidgetColorSettings(Qt::white,
                              Qt::white,
                              this);

    _errorLabel->hide();
    _busWidget->hide();

    connect (_tableWidget, SIGNAL(cellClicked(int,int)),
             this, SLOT(handleCellClicked(int,int)));
    connect (_tableWidget, SIGNAL(cellPressed(int,int)),
             this, SLOT(handleCellClicked(int,int)));
    connect (_confirmButton, SIGNAL(clicked()),
             this, SLOT(handleBusStopConfirmation()));

    updateBusStop();
}

BusBookingPage::~BusBookingPage() {
    delete _busStopLabel;
    delete _busStopChosenLabel;
    delete _busLabel;
    delete _busChosenLabel;
    delete _tableWidget;
    delete _errorLabel;
    delete _busStopWidget;
    delete _busWidget;
    delete _confirmButton;
}

//public
bool BusBookingPage::updateBusStop() {
    if (!findNearbyBusStop()) {
        _errorLabel->show();
        return false;
    }
    _errorLabel->hide();
    return true;
}

//private
bool BusBookingPage::findNearbyBusStop() {

    double latitude = OO;
    double longitude = OO;
    if (!calculateCurrentGpsLocation(latitude, longitude)) {
        QString errorMsg = "gps not working";
        qDebug() << "BusBookingPage -> findNearbyBusStop: "
                 << errorMsg;
        _errorLabel->setText(errorMsg);
        return false;
    }

    JsonReader *jr = JsonReader::getObject();
    if (!jr->loadBusStopsJson()) {
        QString errorMsg = "busstops.json is not loaded";
        qDebug() << "BusBookingPage -> findNearbyBusStop: "
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
        qDebug() << "BusBookingPage -> findNearbyBusStop: "
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

            qDebug() << "BusBookingPage -> findNearbyBusStop: ";
            qDebug() << "row: " << row;
            qDebug() << "col: " << col;
            qDebug() << "text: " << newItem->text();
        }
    }

    return true;
}

double BusBookingPage::calculateDistance(double latitude1,
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

double BusBookingPage::toRadiant(double degree) {
    double rad = degree * PI / DEGREE_180;
    return rad;
}

void BusBookingPage::changeWidgetColorSettings(QColor background,
                                             QColor font,
                                             QWidget *widget) {
    widget->setAutoFillBackground(true);
    QPalette pallete = widget->palette();
    pallete.setColor(widget->backgroundRole(), background);
    pallete.setColor(widget->foregroundRole(), font);
    widget->setPalette(pallete);
}

bool BusBookingPage::calculateCurrentGpsLocation(double &latitude,
                                               double &longitude) {
    latitude = 1.295339;
    longitude = 103.851143;
    return true;
}

//private slots
void BusBookingPage::handleCellClicked(int row, int column) {
    QTableWidgetItem* item = _tableWidget->item(row, column);

    if (item == NULL) {
        return;
    }

    if (!_busWidget->isHidden()) {
        _busChosenLabel->setText(item->text());
    } else if (!_busStopWidget->isHidden()) {
        _busStopChosenLabel->setText(item->text());
    }

    qDebug() << "BusBookingPage -> handleCellClicked: "
                "row: " << row;
    qDebug() << "column: " << column;
    qDebug() << "text: " << item->text();
}

void BusBookingPage::handleBusStopConfirmation() {
    _headerLabel->setText("Choose Your Bus");

    QString key = _busStopChosenLabel->text();
    BusStopObject obj = _objMap[key];

    _busStopWidget->hide();
    _busWidget->show();

    for (int i = _tableWidget->rowCount() - 1; i >= 0; i--) {
        _tableWidget->removeRow(i);
    }

    QStringList header;
    header << "Bus";
    _tableWidget->setHorizontalHeaderLabels(header);
    QVector <QString> busServices = obj.getBusServices();
    for (int i = 0; i < busServices.size(); i++) {
        int row = _tableWidget->rowCount();
        int col = _tableWidget->columnCount() - 1;
        _tableWidget->insertRow(row);

        QString bus = busServices[i];

        if (_busChosenLabel->text() == MSG_NO_BUS) {
            _busChosenLabel->setText(bus);
        }

        QTableWidgetItem *newItem = new QTableWidgetItem(bus);
        newItem->setText(bus);
        newItem->setFlags(newItem->flags()
                          &= ~Qt::ItemIsEditable);
        _tableWidget->setItem(row, col, newItem);
    }

    disconnect (_confirmButton, SIGNAL(clicked()),
                this, SLOT(handleBusStopConfirmation()));
    connect(_confirmButton, SIGNAL(clicked()),
            this, SLOT(handleBusConfirmation()));
}


void BusBookingPage::handleBusConfirmation() {
    _busWidget->show();
    _busStopWidget->show();
    _tableWidget->hide();
    _confirmButton->hide();

    disconnect (_confirmButton, SIGNAL(clicked()),
                this, SLOT(handleBusConfirmation()));
}
