#ifndef BUSREQUESTOBJECT_H
#define BUSREQUESTOBJECT_H

#include <QString>

namespace Object {
    class BusRequestObject;
}

class BusRequestObject {
public:
    explicit BusRequestObject();
    ~BusRequestObject();

public:
    QString getBusStopNumber();
    QString getBusServiceNumber();
    int getNumberOfRequest();
    void setBusStopNumber(QString busStopNumber);
    void setBusServiceNumber(QString busServiceNumber);
    void setNumberOfRequest(int numberOfRequest);

private:
    QString _busStopNumber;
    QString _busServiceNumber;
    int _numberOfRequest;
};
#endif // BUSREQUESTOBJECT_H
