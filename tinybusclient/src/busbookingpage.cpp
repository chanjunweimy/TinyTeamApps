#include "busbookingpage.h"

BusBookingPage::BusBookingPage(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    QWidget* topTabWidget = new QWidget(this);
    QHBoxLayout* topTabLayout = new QHBoxLayout;
    QPushButton* locationButton = new QPushButton(topTabWidget);
    locationButton->setText("Your Location");
    locationButton->setSizePolicy(QSizePolicy::Expanding,
                                  QSizePolicy::Fixed);

    QPushButton* busButton = new QPushButton(topTabWidget);
    busButton->setText("The Bus I Want");
    busButton->setSizePolicy(QSizePolicy::Expanding,
                             QSizePolicy::Fixed);

    topTabLayout->addWidget(locationButton);
    topTabLayout->addWidget(busButton);
    topTabWidget->setLayout(topTabLayout);

    topTabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QVBoxLayout* widgetLayout = new QVBoxLayout;
    widgetLayout->addWidget(topTabWidget);
    this->setLayout(widgetLayout);
}

BusBookingPage::~BusBookingPage() {

}
