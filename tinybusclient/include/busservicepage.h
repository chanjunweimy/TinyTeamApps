#ifndef BUSSERVICEPAGE_H
#define BUSSERVICEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QStringList>
#include <QCompleter>

namespace Gui {
    class BusServicePage;
}

class BusServicePage : public QWidget {
    Q_OBJECT
public:
    BusServicePage();
    ~BusServicePage();

private:
    void setUpInputBox();
    void setUpSubmitButton();

signals:
    void selectedBus(QString busServiceNumber);

private slots:
    void buttonClicked();

private:
    QLineEdit *_inputBox;
    QVBoxLayout *_widgetLayout;

private:
    static const QString INPUT_BOX_LABEL;
    static const QString SUBMIT_BUTTON_LABEL;

};

#endif // BUSSERVICEPAGE_H
