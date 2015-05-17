#include "jsonreader.h"

JsonReader* JsonReader::_jsonReader = NULL;
const QString JsonReader::TYPE_ARRAY = "array";
const QString JsonReader::TYPE_BOOL = "bool";
const QString JsonReader::TYPE_DOUBLE = "double";
const QString JsonReader::TYPE_OBJECT = "object";
const QString JsonReader::TYPE_STRING = "string";
const QString JsonReader::EXT_JSON = ".json";
const QString JsonReader::EXT_BINARY = ".dat";

JsonReader::JsonReader(QObject *parent) :
    QObject(parent) {
}

JsonReader::~JsonReader() {
}

JsonReader* JsonReader::getObject() {
    if (_jsonReader == NULL) {
        _jsonReader = new JsonReader;
    }
    return _jsonReader;
}

void JsonReader::deleteObject() {
    _jsonReader->deleteLater();
    _jsonReader = NULL;
}

//public methods
bool JsonReader::loadBusStopsJson() {
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
    _jsonArray = busStopsJson[param].toArray();
    return true;
}

bool JsonReader::loadBusServicesJson() {
    QJsonObject busServicesJson = loadJsonFile(":/file/local/busServices.json");

    if (busServicesJson.isEmpty()) {
        qDebug() << "BusServicesJsonReader -> loadBusServicesJson: "
                    "busServicesJson is empty!!";
        return false;
    }

    QString param = "busServices";
    if (!isJsonValueExist(busServicesJson, param)) {
        qDebug() << "BusServicesJsonReader -> loadBusServicesJson: "
                    "busServicesJson doesn't have param ( "
                 << param << " )...";
        return false;
    }
    _jsonArray = busServicesJson[param].toArray();
    return true;
}

bool JsonReader::loadBusRequestsJson() {
    QJsonObject busRequestsJson = loadJsonFile(":/file/local/busRequests.json");

    if (busRequestsJson.isEmpty()) {
        qDebug() << "BusRequestsJsonReader -> loadBusRequestsJson: "
                    "busRequestsJson is empty!!";
        return false;
    }

    QString param = "busRequests";
    if (!isJsonValueExist(busRequestsJson, param)) {
        qDebug() << "BusRequestsJsonReader -> loadBusServicesJson: "
                    "busRequestsJson doesn't have param ( "
                 << param << " )...";
        return false;
    }
    _jsonArray = busRequestsJson[param].toArray();
    return true;
}

QVector <BusStopObject> JsonReader::getBusStopObjects() {
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

    for (int i = 0; i < _jsonArray.size(); i++) {
        if (!_jsonArray.at(i).isObject()) {
            busStopObjects.clear();
            return busStopObjects;
        }
        QJsonObject jsonObject = _jsonArray.at(i).toObject();
        if (!isJsonObjectValid(jsonObject, params, typeForParams)){
            busStopObjects.clear();
            return busStopObjects;
        }

        BusStopObject busStopObject;
        busStopObject.setBusStopNumber(
                    jsonObject[BusStopObject::PARAM_BUS_STOP_NUMBER].toString());
        busStopObject.setBusStopDescription(
                    jsonObject[BusStopObject::PARAM_BUS_STOP_DESCRIPTION].toString());

        double latitude = jsonObject[BusStopObject::PARAM_LATITUDE].toDouble();
        busStopObject.setLatitude(latitude);

        double longtitude = jsonObject[BusStopObject::PARAM_LONGITUDE].toDouble();
        busStopObject.setLongtitude(longtitude);

        QJsonArray busServices = jsonObject[
                BusStopObject::PARAM_BUS_SERVICES].toArray();
        for (int j = 0; j < busServices.size(); j++) {
            if (!busServices.at(j).isObject()) {
                busStopObjects.clear();
                return busStopObjects;
            }
            QJsonObject bus = busServices.at(j).toObject();
            if (!isJsonObjectValid(bus,
                                   paramForBusServices,
                                   typeForBusServices)) {
                busStopObjects.clear();
                return busStopObjects;
            }

            busStopObject.addBusService(bus[
                                        BusStopObject::PARAM_BUS_NUMBER].toString());
        }
        busStopObjects.append(busStopObject);

        qDebug() << "JsonReader -> getBusStopObjects: "
                    "created busStopObject: ";
        qDebug() << "number: " << busStopObject.getBusStopNumber();
        qDebug() << "description: " << busStopObject.getBusStopDescription();
        qDebug() << "latitude: " << busStopObject.getLatitude();
        qDebug() << "longitude: " << busStopObject.getLongtitude();
        QVector <QString> buses = busStopObject.getBusServices();
        for (int i = 0; i < buses.size(); i++) {
            qDebug() << "bus " << i << " : " << buses[i];
        }
    }
    return busStopObjects;

}

QVector <BusServicesObject> JsonReader::getBusServiceObjects() {
    QVector <BusServicesObject> busServicesObjects;

    QVector <QString> params = BusServicesObject::getParams();
    QMap <QString, QString> typeForParams =
            BusServicesObject::getTypeForParams(TYPE_STRING,
                                                TYPE_ARRAY);
    QVector <QString> paramForBusStop =
            BusServicesObject::getBusStopParams();
    QMap <QString, QString> typeForBusStopParam =
            BusServicesObject::getTypeForBusStopParams(TYPE_STRING);

    if (_jsonArray.isEmpty()) {
        qWarning() << "BusStopsJsonReader -> getBusServicesObject: "
                      "jsonArray is empty. "
                      "busServicesObjects is therefore empty also..";
        return busServicesObjects;
    }

    for (int i = 0; i < _jsonArray.size(); i++) {
        if (!_jsonArray.at(i).isObject()) {
            busServicesObjects.clear();
            return busServicesObjects;
        }
        QJsonObject jsonObject = _jsonArray.at(i).toObject();
        if (!isJsonObjectValid(jsonObject, params, typeForParams)){
            busServicesObjects.clear();
            return busServicesObjects;
        }

        BusServicesObject busServicesObject;
        busServicesObject.setBusNumber(
                    jsonObject[BusServicesObject::PARAM_BUS_NUMBER].toString());

        QJsonArray busStops = jsonObject[
                BusServicesObject::PARAM_BUS_STOPS].toArray();
        for (int j = 0; j < busStops.size(); j++) {
            if (!busStops.at(j).isObject()) {
                busServicesObjects.clear();
                return busServicesObjects;
            }
            QJsonObject busStop = busStops.at(j).toObject();
            if (!isJsonObjectValid(busStop,
                                   paramForBusStop,
                                   typeForBusStopParam)) {
                busServicesObjects.clear();
                return busServicesObjects;
            }

            busServicesObject.addBusStopNumber(
                        jsonObject[BusServicesObject::PARAM_BUS_STOP_NUMBER].toString());
        }
        busServicesObjects.append(busServicesObject);
    }
    return busServicesObjects;

}

QVector <BusRequestObject> JsonReader::getBusRequestObjects() {

    QVector <BusRequestObject> busRequestObjects;

    QVector <QString> params = BusRequestObject::getParams();
    QMap <QString, QString> typeForParams =
            BusRequestObject::getTypeForParams(TYPE_STRING,
                                               TYPE_DOUBLE);

    if (_jsonArray.isEmpty()) {
        qWarning() << "JsonReader -> getBusRequestObjects: "
                      "jsonArray is empty. "
                      "busRequestObject is therefore empty also..";
        return busRequestObjects;
    }

    for (int i = 0; i < _jsonArray.size(); i++) {
        if (!_jsonArray.at(i).isObject()) {
            busRequestObjects.clear();
            return busRequestObjects;
        }
        QJsonObject jsonObject = _jsonArray.at(i).toObject();
        if (!isJsonObjectValid(jsonObject, params, typeForParams)){
            busRequestObjects.clear();
            return busRequestObjects;
        }

        BusRequestObject busRequestObject;
        QString busStopNumber = jsonObject[BusRequestObject
                ::PARAM_BUS_STOP_NUMBER].toString();
        QString busStopName = jsonObject[BusRequestObject
                ::PARAM_BUS_STOP_NAME].toString();
        QString busServiceNumber = jsonObject[BusRequestObject
                ::PARAM_BUS_SERVICE_NUMBER].toString();
        int numberOfRequest = jsonObject[BusRequestObject
                ::PARAM_NUMBER_OF_REQUEST].toInt();
        busRequestObject.setBusStopNumber(busStopNumber);
        busRequestObject.setBusStopName(busStopName);
        busRequestObject.setBusServiceNumber(busServiceNumber);
        busRequestObject.setNumberOfRequest(numberOfRequest);
        busRequestObjects.append(busRequestObject);
    }

    return busRequestObjects;
}

QJsonArray JsonReader::getJsonArray() {
    if (_jsonArray.isEmpty()) {
        qWarning() << "BusStopsJsonReader -> getJsonArray: "
                      "jsonArray is empty.";
    }

    return _jsonArray;
}

//private methods
bool JsonReader::isJsonValueExist(QJsonValue value) {
    return !value.isNull() && !value.isUndefined();
}

bool JsonReader::isJsonValueExist(QJsonObject json, QString param) {
    return isJsonValueExist(json[param]);
}

bool JsonReader::isJsonObjectValid(QJsonObject jsonObject,
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

        qDebug() << jsonObject[param].toString();

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

QJsonObject JsonReader::loadJsonFile(QString filename) {
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
