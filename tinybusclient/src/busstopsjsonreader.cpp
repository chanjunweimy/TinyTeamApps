#include "busstopsjsonreader.h"

BusStopsJsonReader* BusStopsJsonReader::_busStopsJsonReader = NULL;

BusStopsJsonReader::BusStopsJsonReader(QObject *parent) :
    QObject(parent) {
}

BusStopsJsonReader::~BusStopsJsonReader() {
}

BusStopsJsonReader* BusStopsJsonReader::getObject() {
    if (_busStopsJsonReader == NULL) {
        _busStopsJsonReader = new BusStopsJsonReader;
    }
    return _busStopsJsonReader;
}

void BusStopsJsonReader::deleteObject() {
    _busStopsJsonReader->deleteLater();
    _busStopsJsonReader = NULL;
}
