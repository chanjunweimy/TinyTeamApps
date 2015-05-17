#include "busrequestobject.h"

const QString BusRequestObject::PARAM_BUS_STOP_NUMBER = "busStopNumber";
const QString BusRequestObject::PARAM_BUS_STOP_NAME = "busStopName";
const QString BusRequestObject::PARAM_BUS_SERVICE_NUMBER = "busServiceNumber";
const QString BusRequestObject::PARAM_NUMBER_OF_REQUEST = "numberOfRequest";

QVector <QString> BusRequestObject::_params;
QMap <QString, QString> BusRequestObject::_typeForParams;

BusRequestObject::BusRequestObject() {}

BusRequestObject::~BusRequestObject() {}

QString BusRequestObject::getBusStopNumber() {
    return _busStopNumber;
}

QString BusRequestObject::getBusServiceNumber() {
    return _busServiceNumber;
}

QString BusRequestObject::getBusStopName() {
    return _busStopName;
}

int BusRequestObject::getNumberOfRequest() {
    return _numberOfRequest;
}

void BusRequestObject::setBusStopNumber(QString busStopNumber) {
    _busStopNumber = busStopNumber;
}

void BusRequestObject::setBusServiceNumber(QString busServiceNumber) {
    _busServiceNumber = busServiceNumber;
}

void BusRequestObject::setNumberOfRequest(int numberOfRequest) {
    _numberOfRequest = numberOfRequest;
}

void BusRequestObject::setBusStopName(QString busStopName) {
    _busStopName = busStopName;
}

QVector <QString> BusRequestObject::getParams() {
    if (_params.isEmpty()) {
        _params.append(PARAM_BUS_STOP_NUMBER);
        _params.append(PARAM_BUS_STOP_NAME);
        _params.append(PARAM_BUS_SERVICE_NUMBER);
        _params.append(PARAM_NUMBER_OF_REQUEST);
    }
    return _params;
}

QMap <QString, QString> BusRequestObject::getTypeForParams(QString stringType,
                                                           QString doubleType) {
    if (_typeForParams.isEmpty()) {
        _typeForParams[PARAM_BUS_STOP_NUMBER] = stringType;
        _typeForParams[PARAM_BUS_STOP_NAME] = stringType;
        _typeForParams[PARAM_BUS_SERVICE_NUMBER] = stringType;
        _typeForParams[PARAM_NUMBER_OF_REQUEST] = doubleType;
    }
    return _typeForParams;
}
