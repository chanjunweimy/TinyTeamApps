#include "busrequestobject.h"

BusRequestObject::BusRequestObject() {}

BusRequestObject::~BusRequestObject() {}

QString BusRequestObject::getBusStopNumber() {
    return _busStopNumber;
}

int BusRequestObject::getNumberOfRequest() {
    return _numberOfRequest;
}

void BusRequestObject::setBusStopNumber(QString busStopNumber) {
    _busStopNumber = busStopNumber;
}

void BusRequestObject::setNumberOfRequest(int numberOfRequest) {
    _numberOfRequest = numberOfRequest;
}


