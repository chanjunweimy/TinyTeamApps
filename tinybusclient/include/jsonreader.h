#ifndef JSONREADER
#define JSONREADER

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
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>

#include "busstopobject.h"
#include "busservicesobject.h"
#include "busrequestobject.h"

namespace JsonParser {
    class JsonReader;
}

class JsonReader : public QObject {
    Q_OBJECT

private:
    explicit JsonReader(QObject *parent = 0);
    ~JsonReader();

public:
    static JsonReader* getObject();
    static void deleteObject();

public:
    bool loadBusStopsJson();
    QVector <BusStopObject> getBusStopObjects();
    bool loadBusServicesJson();
    QVector <BusServicesObject> getBusServiceObjects();
    bool loadBusRequestsJson();
    QVector <BusRequestObject> getBusRequestObjects();
    QJsonArray getJsonArray();

private:
    bool isJsonValueExist(QJsonValue value);
    bool isJsonValueExist(QJsonObject json, QString param);
    bool isJsonObjectValid(QJsonObject jsonObject,
                           QVector <QString> params,
                           QMap <QString, QString> typeForParams);
    QJsonObject loadJsonFile(QString filename);
    bool getDriverBusRequestsJsonFromServer();

private slots:
    void handleReplyAfterSendingFile();
    void handleReplyError(QNetworkReply::NetworkError error);
    void showHandshakeSuccessful();

private:
    static JsonReader* _jsonReader;
    QJsonArray _jsonArray;
    QNetworkReply* _reply;

private:
    static const QString TYPE_STRING;
    static const QString TYPE_ARRAY;
    static const QString TYPE_DOUBLE;
    static const QString TYPE_BOOL;
    static const QString TYPE_OBJECT;
    static const QString EXT_JSON;
    static const QString EXT_BINARY;

};

#endif // JSONREADER

