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
#include <QPalette>
#include "jsonreader.h"
#include "busstopobject.h"

namespace Gui {
    class BusServicePage;
}

class BusServicePage : public QWidget {
    Q_OBJECT
public:
    explicit BusServicePage(QWidget * parent = 0,
                            Qt::WindowFlags f = 0);
    ~BusServicePage();

private:
    void setUpInputBox();
    void setUpSubmitButton();
    void setBackgroundColor();
    void setButtonStyleSheet(QPushButton *button);
    void setUpErrorLabel();

signals:
    void busSelected(QString busServiceNumber);

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
