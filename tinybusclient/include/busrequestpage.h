#ifndef BUSREQUESTPAGE_H
#define BUSREQUESTPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QVector>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QIcon>
#include <QHeaderView>

namespace Gui {
    class BusRequestPage;
}

class BusRequestPage : public QWidget {
    Q_OBJECT
public:
    explicit BusRequestPage(QWidget * parent = 0,
                            Qt::WindowFlags f = 0);
    ~BusRequestPage();

public:
    void setBusServiceNumber(QString busServiceNumber);

private:
    void setUpTableWidget();
    void setButtonStyleSheet(QPushButton *button);
    void setUpEndButton();
    void setBackgroundColor();

signals:
    void showBusServicePage();

private slots:
    void buttonClicked();

private:
    QVBoxLayout *_widgetLayout;
    QString _busServiceNumber;

private:
    static const int TABLE_COLUMN_NUMBER;
    static const QString TICK_ICON_FILE;
    static const QString END_BUTTON_LABEL;

};

#endif // BUSREQUESTPAGE_H
