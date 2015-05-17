#ifndef BUSREQUESTOBJECT_H
#define BUSREQUESTOBJECT_H

#include <QString>
#include <QVector>
#include <QMap>

namespace Object {
    class BusRequestObject;
}

class BusRequestObject {
public:
    explicit BusRequestObject();
    ~BusRequestObject();

public:
    QString getBusStopNumber();
    QString getBusStopName();
    QString getBusServiceNumber();
    int getNumberOfRequest();
    void setBusStopNumber(QString busStopNumber);
    void setBusServiceNumber(QString busServiceNumber);
    void setNumberOfRequest(int numberOfRequest);
    void setBusStopName(QString busStopName);

public:
    static QVector <QString> getParams();
    static QMap <QString, QString> getTypeForParams(QString stringType,
                                                    QString doubleType);

private:
    QString _busStopNumber;
    QString _busStopName;
    QString _busServiceNumber;
    int _numberOfRequest;

private:
    static QVector <QString> _params;
    static QMap <QString, QString> _typeForParams;

public:
    static const QString PARAM_BUS_STOP_NUMBER;
    static const QString PARAM_BUS_STOP_NAME;
    static const QString PARAM_BUS_SERVICE_NUMBER;
    static const QString PARAM_NUMBER_OF_REQUEST;
};
#endif // BUSREQUESTOBJECT_H
