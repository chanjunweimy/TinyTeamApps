#include "indexpage.h"

const QString IndexPage::IMAGE_LOGO = ":/image/local/logo.png";
const int IndexPage::MAX_ID_LENGTH = 20;

const QString IndexPage::ROLE_CUSTOMER = "customer";
const QString IndexPage::ROLE_DRIVER = "driver";

IndexPage::IndexPage(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f) {

    changeWidgetColorSettings(QColor(64, 64, 64),
                              QColor(189, 215, 238),
                              this);

    QVBoxLayout* indexPageLayout = new QVBoxLayout;

    QLabel* appName = new QLabel(this);
    appName->setText("Tiny Bus");
    QPalette palette;
    palette.setColor(appName->foregroundRole(), QColor(189, 215, 238));
    appName->setPalette(palette);
    QFont labelFont = appName->font();
    labelFont.setBold(true);
    labelFont.setPointSize(60);
    appName->setAlignment(Qt::AlignCenter);
    appName->setFont(labelFont);

    QLabel* appLogo = new QLabel(this);
    appLogo->setAlignment(Qt::AlignCenter);
    QPixmap appPixmap = QPixmap(QString::fromUtf8(IMAGE_LOGO.toLatin1()));
    appLogo->setPixmap(appPixmap);

    appLogo->setFixedHeight(appLogo->pixmap()->height());

    QLabel* inputBoxLabel = new QLabel(this);
    inputBoxLabel->setText("User ID:");
    inputBoxLabel->setMaximumHeight(inputBoxLabel->sizeHint().height());
    palette.setColor(inputBoxLabel->foregroundRole(), QColor(189, 215, 238));
    inputBoxLabel->setPalette(palette);
    labelFont = inputBoxLabel->font();
    labelFont.setBold(true);
    labelFont.setPointSize(20);
    inputBoxLabel->setFont(labelFont);

    _oneTimeIdLine = new QLineEdit(this);
    _oneTimeIdLine->setMaxLength(MAX_ID_LENGTH);
    QFont inputBoxFont = _oneTimeIdLine->font();
    inputBoxFont.setPointSize(20);
    _oneTimeIdLine->setFont(inputBoxFont);
    _oneTimeIdLine->setPlaceholderText("Please input user ID");

    QPushButton* submitButton = new QPushButton(this);
    submitButton->setText("Submit");
    setButtonStyleSheet(submitButton);

    _errorLabel = new QLabel(this);
    _errorLabel->hide();
    changeWidgetColorSettings(Qt::white,
                              Qt::red,
                              _errorLabel);

    QWidget *dummyWidget = new QWidget();

    indexPageLayout->addWidget(appName);
    indexPageLayout->addWidget(appLogo, Qt::AlignHCenter);
    indexPageLayout->addWidget(inputBoxLabel);
    indexPageLayout->addWidget(_oneTimeIdLine);
    indexPageLayout->addWidget(dummyWidget, 1);
    indexPageLayout->addWidget(submitButton);
    indexPageLayout->addWidget(dummyWidget, 5);
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

void IndexPage::setButtonStyleSheet(QPushButton *button) {
    button->setStyleSheet("background-color: rgb(46, 117, 182);"
                          "border-radius: 7px;"
                          "font: 60px;"
                          "color: white;"
                          "padding: 6px;"
                          "margin: 6px;");
    button->setCursor(Qt::PointingHandCursor);
}
