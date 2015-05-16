#include "busbookingpage.h"

BusBookingPage::BusBookingPage(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    QLabel* topLabel = new QLabel(this);
    changeWidgetColorSettings(Qt::darkGreen,
                              Qt::white,
                              topLabel);

    topLabel->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Maximum);
    topLabel->setText("Bus Stop");
    topLabel->setAlignment(Qt::AlignCenter);
    QFont font = topLabel->font();
    font.setPointSize(18);
    font.setBold(true);
    topLabel->setFont(font);


    LocationPage *locationPage = new LocationPage(this);

    QVBoxLayout* widgetLayout = new QVBoxLayout;
    widgetLayout->addWidget(topLabel);
    widgetLayout->addWidget(locationPage);

    this->setLayout(widgetLayout);

    changeWidgetColorSettings(Qt::white,
                              Qt::white,
                              this);
}

BusBookingPage::~BusBookingPage() {

}


//private
void BusBookingPage::changeWidgetColorSettings(QColor background,
                                               QColor font,
                                               QWidget *widget) {
    widget->setAutoFillBackground(true);
    QPalette pallete = widget->palette();
    pallete.setColor(widget->backgroundRole(), background);
    pallete.setColor(widget->foregroundRole(), font);
    widget->setPalette(pallete);
}
