#ifndef BUSREQUESTPAGE_H
#define BUSREQUESTPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QVector>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QIcon>
#include <QHeaderView>
#include <QScrollBar>
#include <QDebug>
#include "jsonreader.h"
#include "busrequestobject.h"

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
    void addContentToTable();

private:
    void setUpTableWidget();
    void setButtonStyleSheet(QPushButton *button);
    void setUpEndButton();
    void setBackgroundColor();
    void setUpBusServiceLabel();
    void resizeTable();

signals:
    void showBusServicePage();

private slots:
    void buttonClicked();
    void updateNumberOfRequest(int rowNumber);

private:
    QVBoxLayout *_widgetLayout;
    QString _busServiceNumber;
    QLabel *_busServiceLabel;
    QTableWidget *_requestTable;
    QVector<QTableWidgetItem*> _numberOfRequestItems;
    QButtonGroup *_tickButtonGroup;

private:
    static const int TABLE_COLUMN_NUMBER;
    static const QString TICK_ICON_FILE;
    static const QString END_BUTTON_LABEL;

};

#endif // BUSREQUESTPAGE_H
