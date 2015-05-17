#ifndef BUSSERVICESOBJECT
#define BUSSERVICESOBJECT

#include <QVector>
#include <QMap>
#include <QString>
#include <QDebug>

namespace Object {
    class BusServicesObject;
}

class BusServicesObject {
public:
    explicit BusServicesObject();
    ~BusServicesObject();

public:
    QString getBusNumber();
    QVector <QString> getBusStopNumbers();
    void addBusStopNumber(QString busStopNumber);
    void setBusNumber(QString busNumber);
    void setBusStopNumbers(QVector <QString> busStopNumbers);

public:
    static QVector <QString> getParams();
    static QMap <QString, QString> getTypeForParams(QString stringType,
                                                    QString arrayType);
    static QVector <QString> getBusStopParams();
    static QMap <QString, QString> getTypeForBusStopParams(QString stringType);

private:
    static QVector <QString> _params;
    static QMap <QString, QString> _typeForParams;
    static QVector <QString> _busStopParams;
    static QMap <QString, QString> _typeForBusStopParams;

private:
    QString _busNumber;
    QVector <QString> _busStopNumbers;

public:
    static const QString PARAM_BUS_NUMBER;
    static const QString PARAM_BUS_STOPS;
    static const QString PARAM_BUS_STOP_NUMBER;
};

#endif // BUSSERVICESOBJECT

