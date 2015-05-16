#ifndef BUSSTOPOBJECT
#define BUSSTOPOBJECT

#include <QString>
#include <QVector>
#include <QMap>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

namespace Object {
    class BusStopObject;
}

class BusStopObject {
public:
    explicit BusStopObject();
    ~BusStopObject();

public:
    QString getBusStopNumber();
    QString getBusStopDescription();
    double getLatitude();
    double getLongtitude();
    void setBusStopNumber(QString busStopNumber);
    void setBusStopDescription(QString busStopDescription);
    void setLatitude(double latitude);
    void setLongtitude(double longtitude);
    void setBusServices(QVector<QString> busServices);
    void addBusService(QString busService);

public:
    static QVector <QString> getBusServices();
    static QVector <QString> getParams();
    static QMap <QString, QString> getTypeForParams(QString stringType,
                                                    QString arrayType,
                                                    QString doubleType);
    static QVector <QString> getParamForBusServiceArray();
    static QMap <QString, QString> getTypeForBusServiceArray(QString stringType);

public:
    static const QString PARAM_BUS_STOP_NUMBER;
    static const QString PARAM_BUS_SERVICES;
    static const QString PARAM_BUS_STOP_DESCRIPTION;
    static const double PARAM_LATITUDE;
    static const double PARAM_LONGITUDE;

    static const QString PARAM_BUS_NUMBER;


private:
    void initializeClass();

private:
    QString _busStopNumber;
    QString _busStopDescription;
    double _latitude;
    double _longtitude;
    QVector <QString> _busServices;

private:
    static QVector <QString> _params;
    static QMap <QString, QString> _typeForParams;
    static QVector <QString>  _paramForBusServiceArray;
    static QMap <QString, QString> _typeForBusServiceArray;

private:
    static const double OO;


};

#endif // BUSSTOPOBJECT

