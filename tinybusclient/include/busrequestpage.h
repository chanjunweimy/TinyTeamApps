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

namespace Gui {
    class BusRequestPage;
}

class BusRequestPage : public QWidget {
    Q_OBJECT
public:
    BusRequestPage();
    ~BusRequestPage();

private:
    void setUpTableWidget();

signals:

private slots:

private:
    QVBoxLayout *_widgetLayout;

private:
    static const int TABLE_COLUMN_NUMBER;
    static const QString TICK_ICON_FILE;

};

#endif // BUSREQUESTPAGE_H
