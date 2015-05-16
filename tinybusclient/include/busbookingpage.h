#ifndef BUSBOOKINGPAGE
#define BUSBOOKINGPAGE

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QFont>

#include "locationpage.h"

namespace Gui {
    class BusBookingPage;
}

class BusBookingPage : public QWidget {
    Q_OBJECT

public:
    explicit BusBookingPage(QWidget * parent = 0,
                            Qt::WindowFlags f = 0);
    ~BusBookingPage();

private:
    void changeWidgetColorSettings(QColor background,
                                   QColor font,
                                   QWidget* widget);

};


#endif // BUSBOOKINGPAGE

