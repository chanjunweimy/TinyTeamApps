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

namespace Gui {
    class LocationPage;
}

class LocationPage : public QWidget {
    //Q_OBJECT

public:
    explicit LocationPage(QWidget * parent = 0,
                          Qt::WindowFlags f = 0);
    ~LocationPage();

private:
    void changeWidgetColorSettings(QColor background,
                                   QColor font,
                                   QWidget* widget);
    bool calculateCurrentGpsLocation(double& latitude,
                                     double& longitude);

private:
    QLabel* _busStopChosenLabel;
    QTableWidget* _tableWidget;
    QLabel* _errorLabel;

private:
    static const int OO;
};

#endif // LOCATIONPAGE

