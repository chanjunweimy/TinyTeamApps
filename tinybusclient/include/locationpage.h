#ifndef LOCATIONPAGE
#define LOCATIONPAGE

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPalette>
#include <QColor>
#include <QStringList>

#include "jsonreader.h"
#include "busstopobject.h"

namespace Gui {
    class LocationPage;
}

class LocationPage : public QWidget {
    //Q_OBJECT

public:
    explicit LocationPage(QWidget * parent = 0,
                          Qt::WindowFlags f = 0);
    ~LocationPage();

public:
    bool findNearbyBusStop();

private:
    void changeWidgetColorSettings(QColor background,
                                   QColor font,
                                   QWidget* widget);
    bool calculateCurrentGpsLocation(double& latitude,
                                     double& longitude);
    double calculateDistance(double latitude1, double longitude1,
                             double latitude2, double longitude2);

private:
    QLabel* _busStopChosenLabel;
    QTableWidget* _tableWidget;
    QLabel* _errorLabel;

private:
    static const int OO;
    static const double RADIUS_EARTH;
    static const double MAX_DISTANCE;
};

#endif // LOCATIONPAGE

