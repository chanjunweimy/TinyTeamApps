#ifndef INDEXPAGE
#define INDEXPAGE

#include <QObject>
#include <QWidget>
#include <QSizePolicy>
#include <QPixmap>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

namespace Gui {
    class IndexPage;
}

class IndexPage : public QWidget {
    Q_OBJECT

public:
    explicit IndexPage(QWidget * parent = 0,
                       Qt::WindowFlags f = 0);
    ~IndexPage();

private slots:
    void handleReturned();
    void handleButton();

signals:
    void loginSuccessfully(QString role);

private:
    void changeWidgetColorSettings(QColor background,
                                   QColor font,
                                   QWidget* widget);
    void login();
    bool checkId(QString id);

private:
    QLabel* _errorLabel;
    QLineEdit* _oneTimeIdLine;

private:
    static const QString IMAGE_LOGO;
    static const int MAX_ID_LENGTH;

public:
    static const QString ROLE_DRIVER;
    static const QString ROLE_CUSTOMER;
};

#endif // INDEXPAGE

