#include "busrequestobject.h"

BusRequestObject::BusRequestObject() {}

BusRequestObject::~BusRequestObject() {}

QString BusRequestObject::getBusStopNumber() {
    return _busStopNumber;
}

QString BusRequestObject::getBusServiceNumber() {
    return _busServiceNumber;
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


