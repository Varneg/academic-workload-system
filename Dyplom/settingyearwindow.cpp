#include "settingyearwindow.h"
#include "ui_settingyearwindow.h"
#include <QMouseEvent>
#include <QPoint>
#include "ErrorHandler.h"
#include <QIntValidator>

void SettingYearWindow::validation(){
    QIntValidator *intValidator = new QIntValidator(this);

    ui->anualLoadLineEdit->setValidator(intValidator);
    ui->weakLoadLineEdit->setValidator(intValidator);
    ui->yearLineEdit->setValidator(intValidator);
    ui->badImbalanceLineEdit->setValidator(intValidator);
    ui->criticalImbalanceLineEdit->setValidator(intValidator);
}

SettingYearWindow::SettingYearWindow(QWidget *parent, enum WindowType winType, int configYear)
    : QDialog(parent)
    , ui(new Ui::SettingYearWindow)
{
    ui->setupUi(this);
    wT = winType;

    this->setWindowFlags(Qt::FramelessWindowHint);
    UiUtils::setIconOnButton(":/res/img/close.svg", ui->closeButton);

    ui->yearLineEdit->setPlaceholderText("Введіть рік початку навчального року");
    ui->anualLoadLineEdit->setPlaceholderText("Введіть години загального навантаження");
    ui->weakLoadLineEdit->setPlaceholderText("Введіть години недільного навантаження");
    ui->badImbalanceLineEdit->setPlaceholderText("Введіть число");
    ui->criticalImbalanceLineEdit->setPlaceholderText("Введіть число");

    try {
        dbManager = &DatabaseManager::instance();
    } catch (const std::exception& e) {
        ErrorHandler::showError(this, "Не вдалося підєднатися до БД", e);
        this->close();
    }

    validation();

    switch (wT) {
    case WindowType::Adding:
    {
        ui->windowTitle->setText("Додати рік");
        ui->agreeButton->setText("Додати");

        break;
    }
    case WindowType::Editing:
    {
        this->setProperty("configYear", configYear);

        ui->windowTitle->setText("Деталі навантаження");
        ui->agreeButton->setText("Зберігти");

        try {
            QSqlQuery query = dbManager->getYearConfig(configYear);

            if (!query.next()) {
                throw std::runtime_error("Конфігурацію не знайдено або запит повернув 0 рядків");
            }

            ui->yearLineEdit->setText(query.value(0).toString());
            ui->anualLoadLineEdit->setText(query.value(1).toString());
            ui->weakLoadLineEdit->setText(query.value(2).toString());
            ui->badImbalanceLineEdit->setText(query.value(3).toString());
            ui->criticalImbalanceLineEdit->setText(query.value(4).toString());
        } catch (const std::exception& e) {
            ErrorHandler::showError(this, "Помилка з запитом до БД", e);
            this->close();
        }

        break;
    }
    default:
        break;
    }

    UiUtils::setShadowOnAllPushButtons(this);
    UiUtils::setStandardButtonStyle(this, UiUtils::readStyleFile(this, BUTON_STYLE_FILE));
}

SettingYearWindow::~SettingYearWindow()
{
    delete ui;
}

void SettingYearWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QWidget *clickedWidget = childAt(event->pos());

        if (clickedWidget == ui->Headar || ui->Headar->isAncestorOf(clickedWidget)) {
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }
}

void SettingYearWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QWidget *clickedWidget = childAt(event->pos());

        if (clickedWidget == ui->Headar || ui->Headar->isAncestorOf(clickedWidget)) {
            move(event->globalPos() - m_dragPosition);
            event->accept();
        }
    }
}

void SettingYearWindow::on_closeButton_clicked()
{
    this->close();
}


void SettingYearWindow::on_cancelButon_clicked()
{
    this->close();
}

void SettingYearWindow::validateConfigData(YearConfigData data){
    if(data.configYear == -1 || data.anualLoad == -1 || data.weakLoad)
        throw std::runtime_error("Введіть усі обов'язкові дані");
}

YearConfigData SettingYearWindow::getYearConfigFromUI(){
    YearConfigData data;

    data.configYear = UiUtils::parseOrMinusOne(ui->yearLineEdit->text());
    data.anualLoad = UiUtils::parseOrMinusOne(ui->anualLoadLineEdit->text());
    data.weakLoad = UiUtils::parseOrMinusOne(ui->weakLoadLineEdit->text());
    data.badImbalance = UiUtils::parseOrMinusOne(ui->badImbalanceLineEdit->text());
    data.criticalImbalance = UiUtils::parseOrMinusOne(ui->criticalImbalanceLineEdit->text());

    validateConfigData(data);

    return data;
}

void SettingYearWindow::addConfig(){
    try {
        YearConfigData data = getYearConfigFromUI();

        dbManager->addYearConfig(data);
    } catch (const std::exception &e) {
        ErrorHandler::showError(this, "Помилка введення", e);
    }
}

void SettingYearWindow::editConfig(){
    YearConfigData data = getYearConfigFromUI();
    data.newConfigYear = UiUtils::parseOrMinusOne(ui->yearLineEdit->text());
    data.configYear = this->property("configYear").toInt();

    try {
        dbManager->updateYearConfig(data);
    } catch (const std::exception &e) {
        ErrorHandler::showError(this, "Помилка введення", e);
    }
}

void SettingYearWindow::on_agreeButton_clicked()
{
    switch (wT) {
    case WindowType::Adding:{
        addConfig();
        this->close();
        break;
    }
    case WindowType::Editing:
        editConfig();
        this->close();
        break;
    default:
        break;
    }
}

