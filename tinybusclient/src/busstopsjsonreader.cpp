#include "busstopsjsonreader.h"

BusStopsJsonReader* BusStopsJsonReader::_busStopsJsonReader = NULL;
QString BusStopsJsonReader::TYPE_ARRAY = "array";
QString BusStopsJsonReader::TYPE_BOOL = "bool";
QString BusStopsJsonReader::TYPE_DOUBLE = "double";
QString BusStopsJsonReader::TYPE_OBJECT = "object";
QString BusStopsJsonReader::TYPE_STRING = "string";

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

//public methods
bool BusStopsJsonReader::loadBusStopsJson() {
    QJsonObject busStopsJson = loadJsonFile(":/file/local/busstops.json");

    if (busStopsJson.isEmpty()) {
        qDebug() << "BusStopsJsonReader -> loadBusStopsJson: "
                    "busStopsJson is empty!!";
        return false;
    }

    QString param = "busStops";
    if (!isJsonValueExist(busStopsJson, param)) {
        qDebug() << "BusStopJsonReader -> loadBusStopsJson: "
                    "busStopsJson doesn't have param ( "
                 << param << " )...";
        return false;
    }
    _jsonArray = busStopsJson[param];
}

QVector <BusStopObject> BusStopsJsonReader::getBusStopObjects() {
    QVector <BusStopObject> busStopObjects;

    QVector <QString> params = BusStopObject::getParams();
    QMap <QString, QString> typeForParams =
            BusStopObject::getTypeForParams(TYPE_STRING,
                                            TYPE_ARRAY,
                                            TYPE_DOUBLE);
    QVector <QString> paramForBusServices =
            BusStopObject::getParamForBusServiceArray();
    QMap <QString, QString> typeForBusServices =
            BusStopObject::getTypeForBusServiceArray(TYPE_STRING);

    if (_jsonArray.isEmpty()) {
        qWarning() << "BusStopsJsonReader -> getBusStopObjects: "
                      "jsonArray is empty. "
                      "busStopObjects is therefore empty also..";
        return busStopObjects;
    }

    for (int i = 0; i < jsonArray.size(); i++) {
        QJsonObject jsonObject = jsonArray.at(i);
        if (!isJsonObjectValid(jsonObject, params, typeForParams)){
            busStopObjects.clear();
            return busStopObjects;
        }

        BusStopObject busStopObject;
        busStopObject.setBusStopNumber(
                    jsonObject[BusStopObject::PARAM_BUS_STOP_NUMBER].toString());
        busStopObject.setBusStopDescription(
                    jsonObject[BusStopObject::PARAM_BUS_STOP_DESCRIPTION].toString());
        busStopObject.setLatitude(
                    jsonObject[BusStopObject::PARAM_LATITUDE].toDouble());
        busStopObject.setLongtitude(
                    jsonObject[BusStopObject::PARAM_LONGITUDE].toDouble());

        QJsonArray busServices = jsonObject[
                BusStopObject::PARAM_BUS_SERVICES].toArray();
        for (int j = 0; j < busServices.size(); j++) {
            QJsonObject bus = busServices.at(j);
            if (!isJsonObjectValid(bus,
                                   paramForBusServices,
                                   typeForBusServices)) {
                busStopObjects.clear();
                return busStopObjects;
            }

            busStopObject.addBusService(jsonObject[
                                        BusStopObject::PARAM_BUS_NUMBER].toString());
        }
        busStopObjects.append(busStopObject);
    }
    return busStopObjects;

}

QJsonArray BusStopsJsonReader::getJsonArray() {
    if (_jsonArray.isEmpty()) {
        qWarning() << "BusStopsJsonReader -> getJsonArray: "
                      "jsonArray is empty.";
    }

    return _jsonArray;
}

//private methods
bool BusStopsJsonReader::isJsonValueExist(QJsonValue value) {
    return !value.isNull() && !value.isUndefined();
}

bool BusStopsJsonReader::isJsonValueExist(QJsonObject json, QString param) {
    return isJsonValueExist(json[param]);
}

bool BusStopsJsonReader::isJsonObjectValid(QJsonObject jsonObject,
                                           QVector<QString> params,
                                           QMap<QString, QString> typeForParams) {

    for (int i = 0; i < params.size(); i++) {
        QString param = params[i];
        QString type = typeForParams[param];

        qDebug() << "BusStopsJsonReader -> isJsonObjectValid: "
                    "param: " << param << " "
                    "type: " << type;

        if (!isJsonValueExist(jsonObject, param)) {
            qDebug() << "BusStopsJsonReader -> isJsonObjectValid: "
                        "json value is not exist";
            return false;
        }


        if (type == TYPE_STRING && jsonObject[param].isString()) {
        } else if (type == TYPE_ARRAY && jsonObject[param].isArray()) {
        } else if (type == TYPE_DOUBLE && jsonObject[param].isDouble()) {
        } else if (type == TYPE_BOOL && jsonObject[param].isBool()) {
        } else if (type == TYPE_OBJECT && jsonObject[param].isObject()) {
        } else {
            qDebug() << "BusStopsJsonReader -> isJsonObjectValid: "
                        "actual type does not match with expected type";
            return false;
        }
    }
    qDebug() << "BusStopsJsonReader -> isJsonObjectValid: "
                "this jsonObject is valid";
    return true;
}

QJsonObject BusStopsJsonReader::loadJsonFile(QString filename) {
    qDebug() << "BusStopsJsonReader -> loadJsonFile : "
             << "Start loading save file.";

    QJsonObject json;

    QFile loadFile(filename);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qDebug() << "BusStopsJsonReader -> loadJsonFile : "
                 << "Couldn't open save file.";
        return json;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    if (filename.toLower().endsWith(EXT_BINARY)) {
        loadDoc = QJsonDocument::fromBinaryData(saveData);
    } else if (filename.toLower().endsWith(EXT_JSON)) {
    } else {
        assert (false);
    }

    json = loadDoc.object();

    QJsonObject::iterator i;
    for (i = json.begin(); i != json.end(); i++) {
        qDebug() << i.key() << " " << i.value();
    }

    qDebug() << "BusStopsJsonReader -> loadJsonFile : "
             << "Done loading save file.";

    return json;
}