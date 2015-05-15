#ifndef BUSSTOPSJSONREADER
#define BUSSTOPSJSONREADER

#include <QObject>

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

private:
    static BusStopsJsonReader* _busStopsJsonReader;

};

#endif // BUSSTOPSJSONREADER

