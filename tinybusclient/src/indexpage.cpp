#include "indexpage.h"

const QString IndexPage::IMAGE_LOGO = ":/image/local/logo.jpg";
const int IndexPage::MAX_ID_LENGTH = 20;

const QString IndexPage::ROLE_CUSTOMER = "customer";
const QString IndexPage::ROLE_DRIVER = "driver";

IndexPage::IndexPage(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    QVBoxLayout* indexPageLayout = new QVBoxLayout;

    QLabel* appLogo = new QLabel(this);
    appLogo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPixmap appPixmap = QPixmap(QString::fromUtf8(IMAGE_LOGO.toLatin1()));
    appLogo->setPixmap(appPixmap);

    appLogo->setFixedHeight(appLogo->pixmap()->height());
    appLogo->setFixedWidth(appLogo->pixmap()->width());


    _oneTimeIdLine = new QLineEdit(this);
    _oneTimeIdLine->setMaxLength(MAX_ID_LENGTH);

    QPushButton* submitButton = new QPushButton(this);
    submitButton->setText("Submit");

    _errorLabel = new QLabel(this);
    _errorLabel->hide();
    changeWidgetColorSettings(Qt::white,
                              Qt::red,
                              _errorLabel);

    indexPageLayout->addWidget(appLogo);
    indexPageLayout->addWidget(_oneTimeIdLine);
    indexPageLayout->addWidget(submitButton);
    this->setLayout(indexPageLayout);

    connect(_oneTimeIdLine, SIGNAL(returnPressed()),
            this, SLOT(handleReturned()));
    connect(submitButton, SIGNAL(clicked()),
            this, SLOT(handleButton()));
}

IndexPage::~IndexPage() {
    delete _errorLabel;
    delete _oneTimeIdLine;
}

//private slots
void IndexPage::handleReturned() {
    login();
}

void IndexPage::handleButton() {
    login();
}

//private
void IndexPage::changeWidgetColorSettings(QColor background,
                                          QColor font,
                                          QWidget *widget) {

    widget->setAutoFillBackground(true);
    QPalette pallete = widget->palette();
    pallete.setColor(widget->backgroundRole(), background);
    pallete.setColor(widget->foregroundRole(), font);
    widget->setPalette(pallete);
}

void IndexPage::login() {
    QString id = _oneTimeIdLine->text();
    if (checkId(id)) {
        QString role = ROLE_DRIVER;
        _errorLabel->hide();
        emit this->loginSuccessfully(role);
        return;
    }

    _errorLabel->setText("Error: ID is not correct!");
    _errorLabel->show();
}

bool IndexPage::checkId(QString id) {
    //to do: check with server
    Q_UNUSED(id);

    return true;
}
