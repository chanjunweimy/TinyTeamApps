#ifndef BUSBOOKINGPAGE
#define BUSBOOKINGPAGE

#include <cmath>

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
#include <QPushButton>
#include <QHeaderView>
#include <QMap>

#include "jsonreader.h"
#include "busstopobject.h"

namespace Gui {
    class BusBookingPage;
}

class BusBookingPage : public QWidget {
    Q_OBJECT

public:
    explicit BusBookingPage(QWidget * parent = 0,
                          Qt::WindowFlags f = 0);
    ~BusBookingPage();

public:
    bool updateBusStop();

private:
    bool findNearbyBusStop();

    void changeWidgetColorSettings(QColor background,
                                   QColor font,
                                   QWidget* widget);
    bool calculateCurrentGpsLocation(double& latitude,
                                     double& longitude);
    double calculateDistance(double latitude1, double longitude1,
                             double latitude2, double longitude2);
    double toRadiant(double degree);
    void setButtonStyleSheet(QPushButton *button);

private slots:
    void handleCellClicked(int row, int column);
    void handleBusStopConfirmation();
    void handleBusConfirmation();

private:
    QLabel* _headerLabel;
    QLabel* _busLabel;
    QLabel* _busStopLabel;
    QLabel* _busChosenLabel;
    QLabel* _busStopChosenLabel;
    QTableWidget* _tableWidget;
    QWidget *_busWidget;
    QWidget *_busStopWidget;
    QLabel* _errorLabel;
    QPushButton* _confirmButton;
    QMap <QString, BusStopObject> _objMap;

private:
    static const int OO;
    static const double RADIUS_EARTH;
    static const double PI;
    static const double DEGREE_180;
    static const double MAX_DISTANCE;
    static const QString MSG_NO_BUS_STOP;
    static const QString MSG_NO_BUS;
};

#endif // BUSBOOKINGPAGE

