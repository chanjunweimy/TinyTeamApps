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
    int getNumberOfRequest();
    void setBusStopNumber(QString busStopNumber);
    void setNumberOfRequest(int numberOfRequest);

private:
    QString _busStopNumber;
    int _numberOfRequest;
};
#endif // BUSREQUESTOBJECT_H
