#include "busstopobject.h"

double BusStopObject::OO = 0;
QString BusStopObject::PARAM_BUS_STOP_NUMBER = "busStopNumber";
QString BusStopObject::PARAM_BUS_SERVICES = "busServices";
QString BusStopObject::PARAM_BUS_STOP_DESCRIPTION = "busStopDescription";
double BusStopObject::PARAM_LATITUDE = "latitude";
double BusStopObject::PARAM_LONGITUDE = "longitude";

QString BusStopObject::PARAM_BUS_NUMBER = "busNumber";

BusStopObject::BusStopObject() {
    initializeClass();
}

BusStopObject::~BusStopObject() {
}


//public methods
QVector <QString> BusStopObject::getBusServices() {
    if (_busServices.isEmpty()) {
        qWarning() << "BusStopObject -> getBusServices: "
                      "_busServices is empty. :O";
    }

    return _busServices;
}

QString BusStopObject::getBusStopNumber() {
    if (_busStopNumber.isEmpty()) {
        qWarning() << "BusStopObject -> getBusStopNumber: "
                      "_busStopNumber is empty. :O";
    }

    return _busStopNumber;
}

QString BusStopObject::getBusStopDescription() {
    if (_busStopDescription.isEmpty()) {
        qWarning() << "BusStopObject -> getBusStopDescription: "
                      "_busStopDescription is empty. :O";
    }

    return _busStopDescription;
}

double BusStopObject::getLatitude() {
    if (_latitude == OO) {
        qWarning() << "BusStopObject -> getLatitude: "
                      "_latitude is not exist...";
    }

    return _latitude;
}

double BusStopObject::getLongtitude() {
    if (_longtitude == OO) {
        qWarning() << "BusStopObject -> getLongtitude: "
                      "_longtitude is not exist...";
    }

    return _longtitude;
}

QVector <QString> BusStopObject::getParams() {
    if (_params.isEmpty()) {
        _params.append(PARAM_BUS_STOP_NUMBER);
        _params.append(PARAM_BUS_STOP_DESCRIPTION);
        _params.append(PARAM_LATITUDE);
        _params.append(PARAM_LONGITUDE);
        _params.append(PARAM_BUS_SERVICES);

    }
    return _params;
}

QMap <QString, QString> BusStopObject::getTypeForParams(QString stringType,
                                                        QString arrayType,
                                                        QString doubleType) {
    if (_typeForParams.isEmpty()) {
        _typeForParams[PARAM_BUS_STOP_NUMBER] = stringType;
        _typeForParams[PARAM_BUS_STOP_DESCRIPTION] = stringType;
        _typeForParams[PARAM_LATITUDE] = doubleType;
        _typeForParams[PARAM_LONGITUDE] = doubleType;
        _typeForParams[PARAM_BUS_SERVICES] = arrayType;
    }
    return _typeForParams;
}

QVector <QString> BusStopObject::getParamForBusServiceArray() {
    if (_paramForBusServiceArray.isEmpty()) {
        _paramForBusServiceArray.append(PARAM_BUS_NUMBER);
    }
    return _paramForBusServiceArray;
}

QMap <QString, QString> BusStopObject::getTypeForBusServiceArray(QString stringType) {
    if (_typeForBusServiceArray.isEmpty()) {
        _typeForBusServiceArray[PARAM_BUS_NUMBER] = stringType;
    }
    return _typeForBusServiceArray;
}


void BusStopObject::setBusServices(QVector<QString> busServices) {
    _busServices.clear();
    _busServices += busServices;
}

void BusStopObject::addBusService(QString busService) {
    _busServices.append(busService);
}

void BusStopObject::setBusStopNumber(QString busStopNumber) {
    _busStopNumber = busStopNumber;
}

void BusStopObject::setLatitude(double latitude) {
    _latitude = latitude;
}

void BusStopObject::setLongtitude(double longtitude) {
    _longtitude = longtitude;
}

//private
void BusStopObject::initializeClass() {
    _latitude = OO;
    _longtitude = OO;
}
