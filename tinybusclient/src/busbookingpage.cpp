#include "busbookingpage.h"

BusBookingPage::BusBookingPage(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    QWidget* topTabWidget = new QWidget(this);
    QHBoxLayout* topTabLayout = new QHBoxLayout;
    QPushButton* locationButton = new QPushButton(topTabWidget);
    locationButton->setText("Your Location");

    QPushButton* busButton = new QPushButton(topTabWidget);
    locationButton->setText("The Bus I Want");

    topTabLayout->addWidget(locationButton);
    topTabLayout->addWidget(busButton);
    topTabWidget->setLayout(topTabLayout);

    topTabWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
}

BusBookingPage::~BusBookingPage() {

}
