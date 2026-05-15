#include "specialityprocesswindow.h"
#include "ui_specialityprocesswindow.h"
#include <QMouseEvent>
#include <QPoint>
#include "ErrorHandler.h"
#include <QIntValidator>

void SpecialityProcessWindow::validation(){
    ui->specialityNumberLineEdit->setValidator(new QIntValidator());
}

SpecialityProcessWindow::SpecialityProcessWindow(QWidget *parent, enum WindowType winType, int specialityNumber)
    : QDialog(parent)
    , ui(new Ui::SpecialityProcessWindow)
{
    ui->setupUi(this);
    wT = winType;

    this->setWindowFlags(Qt::FramelessWindowHint);
    UiUtils::setIconOnButton(":/res/img/close.svg", ui->closeButton);

    ui->departmentComboBox->lineEdit()->setPlaceholderText("Оберіть факультет");
    ui->specialityNameLineEdit->setPlaceholderText("Введіть назву спеціальності");
    ui->specialityNumberLineEdit->setPlaceholderText("Введіть номер спеціальності ");

    try {
        dbManager = &DatabaseManager::instance();
    } catch (const std::exception& e) {
        ErrorHandler::showError(this, "Не вдалося підєднатися до БД", e);
        this->close();
    }

    try {
        ui->departmentComboBox->setDbHandlers(
            [this]() { return dbManager->getAllDepartment(); },
            [this](int id, const QString& text) { dbManager->updateDepartment(id, text); },
            [this](const QString& text) { dbManager->addDepartment(text); },
            [this](int id) { dbManager->deleteDepartment(id); },
            true
            );
    }catch(const std::exception& e){
        ErrorHandler::showError(this, "Не вдалося отримати дані з БД", e);
        this->close();
    }

    validation();

    switch (wT) {
    case WindowType::Adding:
    {
        ui->windowTitle->setText("Додати викладача");
        ui->agreeButton->setText("Додати");

        break;
    }
    case WindowType::Editing:
    {
        ui->windowTitle->setText("Редагування викладча");
        ui->agreeButton->setText("Зберігти");

        this->setProperty("specialityNumber", specialityNumber);

        try {
            QSqlQuery query = dbManager->getSpecialityByID(specialityNumber);

            if (!query.next()) {
                throw std::runtime_error("Викладача не знайдено або запит повернув 0 рядків");
            }

            ui->specialityNumberLineEdit->setText(QString::number(specialityNumber));
            ui->departmentComboBox->setCurrentIndex(ui->departmentComboBox->findData(query.value(0).toInt()));
            ui->specialityNameLineEdit->setText(query.value(1).toString());
            ui->specialityNumberLineEdit->setEnabled(false);

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

SpecialityProcessWindow::~SpecialityProcessWindow()
{
    delete ui;
}

void SpecialityProcessWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QWidget *clickedWidget = childAt(event->pos());

        if (clickedWidget == ui->Headar || ui->Headar->isAncestorOf(clickedWidget)) {
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }
}

void SpecialityProcessWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QWidget *clickedWidget = childAt(event->pos());

        if (clickedWidget == ui->Headar || ui->Headar->isAncestorOf(clickedWidget)) {
            move(event->globalPos() - m_dragPosition);
            event->accept();
        }
    }
}

void SpecialityProcessWindow::on_closeButton_clicked()
{
    this->close();
}


void SpecialityProcessWindow::on_cancelButon_clicked()
{
    this->close();
}

void SpecialityProcessWindow::addSpeciality(){
    int specialityNumber = UiUtils::parseOrMinusOne(ui->specialityNumberLineEdit->text());
    int departmentID = UiUtils::parseOrMinusOne(ui->departmentComboBox->currentData());
    QString specialityName = UiUtils::parseOrNull(ui->specialityNameLineEdit->text());

    try {
        dbManager->addSpeciality(specialityNumber, departmentID, specialityName);
    } catch (const std::exception &e) {
        ErrorHandler::showError(this, "Помилка введення", e);
    }
}

void SpecialityProcessWindow::editSpeciality(){
    int specialityNumber = UiUtils::parseOrMinusOne(ui->specialityNumberLineEdit->text());
    int departmentID = UiUtils::parseOrMinusOne(ui->departmentComboBox->currentData());
    QString specialityName = UiUtils::parseOrNull(ui->specialityNameLineEdit->text());

    try {
        dbManager->updateSpeciality(specialityNumber, departmentID, specialityName);
    } catch (const std::exception &e) {
        ErrorHandler::showError(this, "Помилка введення", e);
    }
}

void SpecialityProcessWindow::on_agreeButton_clicked()
{
    switch (wT) {
    case WindowType::Adding:{
        addSpeciality();
        this->close();
        break;
    }
    case WindowType::Editing:
        editSpeciality();
        this->close();
        break;
    default:
        break;
    }
}

