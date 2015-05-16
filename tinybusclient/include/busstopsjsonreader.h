#ifndef BUSSTOPSJSONREADER
#define BUSSTOPSJSONREADER

#include <cassert>

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QIODevice>
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QString>

#include "busstopobject.h"

namespace JsonParser {
    class BusStopsJsonReader;
}

class BusStopsJsonReader : public QObject {
    Q_OBJECT

private:
    explicit BusStopsJsonReader(QObject *parent = 0);
    ~BusStopsJsonReader();

public:
    BusStopsJsonReader* getObject();
    void deleteObject();

public:
    bool loadBusStopsJson();
    QVector <BusStopObject> getBusStopObjects();
    QJsonArray getJsonArray();

private:
    bool isJsonValueExist(QJsonValue value);
    bool isJsonValueExist(QJsonObject json, QString param);
    bool isJsonObjectValid(QJsonObject jsonObject,
                           QVector <QString> params,
                           QMap <QString, QString> typeForParams);
    QJsonObject loadJsonFile(QString filename);

private:
    static BusStopsJsonReader* _busStopsJsonReader;
    QJsonArray _jsonArray;

private:
    static const QString TYPE_STRING;
    static const QString TYPE_ARRAY;
    static const QString TYPE_DOUBLE;
    static const QString TYPE_BOOL;
    static const QString TYPE_OBJECT;
    static const QString EXT_JSON;
    static const QString EXT_BINARY;

};

#endif // BUSSTOPSJSONREADER

