#include "busservicesobject.h"

const QString BusServicesObject::PARAM_BUS_NUMBER = "busNumber";
const QString BusServicesObject::PARAM_BUS_STOPS = "busStops";
const QString BusServicesObject::PARAM_BUS_STOP_NUMBER = "busStopNumber";


QVector <QString> BusServicesObject::_params;
QMap <QString, QString> BusServicesObject::_typeForParams;
QVector <QString> BusServicesObject::_busStopParams;
QMap <QString, QString> BusServicesObject::_typeForBusStopParams;


BusServicesObject::BusServicesObject() {
}

BusServicesObject::~BusServicesObject() {
}

//public
QString BusServicesObject::getBusNumber() {
    if (_busNumber.isEmpty()) {
        qWarning() << "BusServicesObject -> getBusNumber: "
                      "_busNumber is empty..";
    }
    return _busNumber;
}

QVector <QString> BusServicesObject::getBusStopNumbers() {
    if (_busStopNumbers.isEmpty()) {
        qWarning() << "BusServicesObject -> getBusStopNumbers: "
                      "_busStopNumbers is empty..";
    }
    return _busStopNumbers;
}

void BusServicesObject::addBusStopNumber(QString busStopNumber) {
    _busStopNumbers.append(busStopNumber);
}

void BusServicesObject::setBusNumber(QString busNumber) {
    _busNumber = busNumber;
}

void BusServicesObject::setBusStopNumbers(QVector<QString> busStopNumbers) {
    if (!_busStopNumbers.isEmpty()) {
        qWarning() << "BusServicesObject -> setBusStopNumbers: "
                      "_busStopNumbers are going to be replaced";
        qDebug() << "old _busStopNumbers: ";
        for (int i = 0; i < _busStopNumbers.size(); i++ ) {
            qDebug() << _busStopNumbers.at(i);
        }
    }

    _busStopNumbers.clear();
    _busStopNumbers += busStopNumbers;

    qDebug() << "BusServicesOject -> setBusStopBumbers: ";
    qDebug() << "new _busStopNumbers: ";
    for (int i = 0; i < _busStopNumbers.size(); i++ ) {
        qDebug() << _busStopNumbers.at(i);
    }
}


//public static
QVector <QString> BusServicesObject::getParams() {
    if (_params.isEmpty()) {
        _params.append(PARAM_BUS_NUMBER);
        _params.append(PARAM_BUS_STOPS);
    }
    return _params;
}

QMap <QString, QString> BusServicesObject::getTypeForParams(QString stringType,
                                                            QString arrayType) {
    if (_typeForParams.isEmpty()) {
        _typeForParams[PARAM_BUS_NUMBER] = stringType;
        _typeForParams[PARAM_BUS_STOPS] = arrayType;
    }
    return _typeForParams;
}

QVector <QString> BusServicesObject::getBusStopParams() {
    if (_busStopParams.isEmpty()) {
        _busStopParams.append(PARAM_BUS_STOP_NUMBER);
    }
    return _busStopParams;
}

QMap <QString, QString> BusServicesObject::getTypeForBusStopParams(QString stringType) {
    if (_typeForBusStopParams.isEmpty()) {
        _typeForBusStopParams[PARAM_BUS_STOP_NUMBER] = stringType;
    }
    return _typeForBusStopParams;
}
