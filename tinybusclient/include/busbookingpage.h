#ifndef BUSBOOKINGPAGE
#define BUSBOOKINGPAGE

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>

namespace Gui {
    class BusBookingPage;
}

class BusBookingPage : public QWidget {
    Q_OBJECT

public:
    explicit BusBookingPage(QWidget * parent = 0,
                            Qt::WindowFlags f = 0);
    ~BusBookingPage();

};


#endif // BUSBOOKINGPAGE

