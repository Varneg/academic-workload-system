#include "disciplineprocesswindow.h"
#include "ui_disciplineprocesswindow.h"
#include <QMouseEvent>
#include <QPoint>
#include <QCompleter>
#include "ErrorHandler.h"
#include <QSqlQuery>
#include <QIntValidator>
#include <QDoubleValidator>

void DisciplineProcessWindow::validation(){
    QIntValidator *intValidator = new QIntValidator(this);

    ui->semestrLineEdit->setValidator(intValidator);
    ui->quantityStudent->setValidator(intValidator);
    ui->totalHourLineEdit->setValidator(intValidator);
    ui->semestrLineEdit->setValidator(new QIntValidator(1, 20, this));

    QDoubleValidator *hourPerWeakValidator = new QDoubleValidator(this);
    hourPerWeakValidator->setDecimals(3);
    hourPerWeakValidator->setNotation(QDoubleValidator::StandardNotation);
    hourPerWeakValidator->setLocale(QLocale::c());
    ui->hourPerWeakLineEdit->setValidator(hourPerWeakValidator);
}

DisciplineProcessWindow::DisciplineProcessWindow(QWidget *parent, enum WindowType winType, int configYear, int id)
    : QDialog(parent)
    , ui(new Ui::DisciplineProcessWindow)
{
    ui->setupUi(this);
    wT = winType;
    m_configYear = configYear;

    this->setWindowFlags(Qt::FramelessWindowHint);
    UiUtils::setIconOnButton(":/res/img/close.svg", ui->closeButton);

    ui->groupComboBox->lineEdit()->setPlaceholderText("Оберіть групу");
    ui->disciplineComboBox->lineEdit()->setPlaceholderText("Оберіть дисципліни");
    ui->typeDisciplineComboBox->lineEdit()->setPlaceholderText("Оберіть тип дисципліни");
    ui->teacherComboBox->lineEdit()->setPlaceholderText("Оберіть викладача");

    ui->totalHourLineEdit->setPlaceholderText("Введіть кількість годин");
    ui->hourPerWeakLineEdit->setPlaceholderText("Введіть кільість годин");
    ui->semestrLineEdit->setPlaceholderText("Введіть семестр");
    ui->quantityStudent->setPlaceholderText("Введіть кількість студентів");

    try {
        dbManager = &DatabaseManager::instance();
    } catch (const std::exception& e) {
        ErrorHandler::showError(this, "Не вдалося підєднатися до БД", e);
        this->close();
    }

    try {
        ui->disciplineComboBox->setDbHandlers(
            [this]() { return dbManager->getAllDiscipline(); },
            [this](int id, const QString& text) { dbManager->updateDiscipline(id, text); },
            [this](const QString& text) { dbManager->addDiscipline(text); },
            [this](int id) { dbManager->deleteDiscipline(id); },
            true
            );

        ui->typeDisciplineComboBox->setDbHandlers(
            [this]() { return dbManager->getAllDisciplineType(); },
            [this](int id, const QString& text) { dbManager->updateDisciplineType(id, text); },
            [this](const QString& text) { dbManager->addDisciplineType(text); },
            [this](int id) { dbManager->deleteDisciplineType(id); },
            true
            );

        ui->groupComboBox->setDbHandlers(
            [this]() { return dbManager->getAllGroup(); }
            );

        ui->teacherComboBox->setDbHandlers(
            [this]() {return dbManager->getAllTeacherPIB();}
            );
    } catch (const std::exception& e) {
        ErrorHandler::showError(this, "Не вдалося отримати дані з БД", e);
        this->close();
    }

    validation();

    switch (wT) {
    case WindowType::Adding:
    {
        ui->windowTitle->setText("Додати дисципліну");
        ui->agreeButton->setText("Додати");

        break;
    }
    case WindowType::Editing:
    {
        this->setProperty("disciplineActivityID", id);

        ui->windowTitle->setText("Редагування дисципліни");
        ui->agreeButton->setText("Зберігти");

        try {
            QSqlQuery query = dbManager->getDisciplineActivityByID(id);

            if (!query.next()) {
                throw std::runtime_error("Активність не знайдено або запит повернув 0 рядків");
            }

            ui->disciplineComboBox->setCurrentIndex(ui->disciplineComboBox->findData(query.value(0).toInt()));
            ui->typeDisciplineComboBox->setCurrentIndex(ui->typeDisciplineComboBox->findData(query.value(1).toInt()));
            ui->groupComboBox->setCurrentIndex(ui->groupComboBox->findData(query.value(2).toInt()));
            ui->teacherComboBox->setCurrentIndex(ui->teacherComboBox->findData(query.value(3).toInt()));

            ui->totalHourLineEdit->setText(query.value(4).toInt() <= 0 ? "" : query.value(4).toString());
            ui->hourPerWeakLineEdit->setText(query.value(5).toFloat() <= 0 ? "" : query.value(5).toString());
            ui->semestrLineEdit->setText(query.value(6).toString());
            ui->quantityStudent->setText(query.value(7).toInt() <= 0 ? "" : query.value(7).toString());

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

DisciplineProcessWindow::~DisciplineProcessWindow()
{
    delete ui;
}

void DisciplineProcessWindow::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        QWidget *clickedWidget = childAt(event->pos());

        if (clickedWidget == ui->Headar || ui->Headar->isAncestorOf(clickedWidget)) {
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }
}

void DisciplineProcessWindow::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton) {
        QWidget *clickedWidget = childAt(event->pos());

        if (clickedWidget == ui->Headar || ui->Headar->isAncestorOf(clickedWidget)) {
            move(event->globalPos() - m_dragPosition);
            event->accept();
        }
    }
}

void DisciplineProcessWindow::on_closeButton_clicked()
{
    this->close();
}


void DisciplineProcessWindow::on_cancelButon_clicked()
{
    this->close();
}

void DisciplineProcessWindow::validateActivityData(DisciplineActivityData data){
    if(data.disciplineID == -1 || data.disciplineTypeID == -1 || data.groupID == -1)
        throw std::runtime_error("Введіть усі обов'язкові дані");
}

DisciplineActivityData DisciplineProcessWindow::getDisciplineActivityDataFromUI(){
    DisciplineActivityData data;

    data.disciplineID = UiUtils::parseOrMinusOne(ui->disciplineComboBox->currentData());
    data.disciplineTypeID = UiUtils::parseOrMinusOne(ui->typeDisciplineComboBox->currentData());
    data.groupID = UiUtils::parseOrMinusOne(ui->groupComboBox->currentData());
    data.teacherID = UiUtils::parseOrMinusOne(ui->teacherComboBox->currentData());
    data.totalHour = UiUtils::parseOrMinusOne(ui->totalHourLineEdit->text());
    data.hourPerWeek = UiUtils::parseOrMinusOne(ui->hourPerWeakLineEdit->text());
    data.semestr = UiUtils::parseOrMinusOne(ui->semestrLineEdit->text());
    data.quantityStudent = UiUtils::parseOrMinusOne(ui->quantityStudent->text());
    data.currentYear = m_configYear;

    validateActivityData(data);

    return data;
}

void DisciplineProcessWindow::addDisciplineActivity(){
    try {
        DisciplineActivityData data = getDisciplineActivityDataFromUI();

        dbManager->addDisciplineActivity(data);
        this->close();
    } catch (const std::exception& e) {
        ErrorHandler::showError(this, "Невдалося додати активність", e);
    }
}

void DisciplineProcessWindow::edditDisciplineActivity(){
    DisciplineActivityData data = getDisciplineActivityDataFromUI();
    data.disciplineActivityID = this->property("disciplineActivityID").toInt();

    try {
        dbManager->updateDisciplineActivity(data);
        this->close();
    } catch (const std::exception& e) {
        ErrorHandler::showError(this, "Невдалося додати активність", e);
    }
}

void DisciplineProcessWindow::on_agreeButton_clicked(){
    switch (wT) {
    case WindowType::Adding:{
        addDisciplineActivity();
        break;
    }
    case WindowType::Editing:{
        edditDisciplineActivity();
        break;
    }
    default:
        break;
    }
}

void DisciplineProcessWindow::unblockAllWidget(){
    UiUtils::unblockWidget(ui->semestrLineEdit);
    UiUtils::unblockWidget(ui->totalHourLineEdit);
    UiUtils::unblockWidget(ui->hourPerWeakLineEdit);
    UiUtils::unblockWidget(ui->quantityStudent);
}

void DisciplineProcessWindow::on_typeDisciplineComboBox_currentIndexChanged(int index)
{
    int typeId = ui->typeDisciplineComboBox->currentData().toInt();

    unblockAllWidget();

    switch (typeId) {
        case 4:{
            ui->totalHourLineEdit->clear();
            UiUtils::blockWidget(ui->hourPerWeakLineEdit);

            break;
        }
        case 5:{
            ui->totalHourLineEdit->clear();
            UiUtils::blockWidget(ui->totalHourLineEdit);

            ui->hourPerWeakLineEdit->clear();
            UiUtils::blockWidget(ui->hourPerWeakLineEdit);

            break;
        }
        default:{
            break;
        }
    }
}