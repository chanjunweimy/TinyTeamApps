#ifndef BUSSERVICEPAGE_H
#define BUSSERVICEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>

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

private slots:
    void buttonClicked();

private:
    QLineEdit *_inputBox;
    QVBoxLayout *_widgetLayout;
};

#endif // BUSSERVICEPAGE_H
