#include "teacherprocesswindow.h"
#include "ui_teacherprocesswindow.h"
#include <QMouseEvent>
#include <QPoint>
#include "ErrorHandler.h"
#include <QSqlQueryModel>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDebug>
#include <QIntValidator>

void TeacherProcessWindow::validation(){
    QRegularExpression regex("^[A-Za-zА-Яа-яІіЇїЄє]+(-[A-Za-zА-Яа-яІіЇїЄє]+)*( [A-Za-zА-Яа-яІіЇїЄє]+(-[A-Za-zА-Яа-яІіЇїЄє]+)*){1,2}$");
    QValidator *PIBValidator = new QRegularExpressionValidator(regex, this);
    ui->PIBLineEdit->setValidator(PIBValidator);

    QDoubleValidator *rateValidator = new QDoubleValidator(this);
    rateValidator->setDecimals(3);
    rateValidator->setNotation(QDoubleValidator::StandardNotation);
    rateValidator->setLocale(QLocale::c());
    ui->rateLineEdit->setValidator(rateValidator);

    ui->otherLoadLineEdit->setValidator(new QIntValidator(this));
}

TeacherProcessWindow::TeacherProcessWindow(QWidget *parent, enum WindowType winType, int id, int configYear)
    : QDialog(parent)
    , ui(new Ui::TeacherProcessWindow)
{
    ui->setupUi(this);

    wT = winType;

    this->setWindowFlags(Qt::FramelessWindowHint);
    UiUtils::setIconOnButton(":/res/img/close.svg", ui->closeButton);

    try {
        dbManager = &DatabaseManager::instance();
    } catch (const std::exception& e) {
        ErrorHandler::showError(this, "Не вдалося підєднатися до БД", e);
        this->close();
    }

    try {
        ui->postComboBox->setDbHandlers(
            [this]() { return dbManager->getAllPost(); },
            [this](int id, const QString& text) { dbManager->updatePost(id, text); },
            [this](const QString& text) { dbManager->addPost(text); },
            [this](int id) { dbManager->deletePost(id); },
            true
            );
    }catch(const std::exception& e){
        ErrorHandler::showError(this, "Не вдалося отримати дані з БД", e);
        this->close();
    }


    UiUtils::setShadowOnAllPushButtons(this);
    UiUtils::setStandardButtonStyle(this, UiUtils::readStyleFile(this, BUTON_STYLE_FILE));

    ui->PIBLineEdit->setPlaceholderText("Введіть ПІБ викладача");
    ui->rateLineEdit->setPlaceholderText("Введіть ставку викладача");
    ui->otherLoadLineEdit->setPlaceholderText("Введіть інше навантаження");
    ui->postComboBox->lineEdit()->setPlaceholderText("Оберіть посаду");

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

        this->setProperty("teacherId", id);
        this->setProperty("configYear", configYear);

        try {
            QSqlQuery query = dbManager->getTeacherDataByID(id, configYear);

            if (!query.next()) {
                throw std::runtime_error("Викладача не знайдено або запит повернув 0 рядків");
            }

            ui->PIBLineEdit->setText(query.value(0).toString());
            ui->postComboBox->setCurrentIndex(ui->postComboBox->findData(query.value(1).toInt()));
            ui->rateLineEdit->setText(query.value(2).toString());
            ui->otherLoadLineEdit->setText(query.value(3).toString());
        } catch (const std::exception& e) {
            ErrorHandler::showError(this, "Помилка з запитом до БД", e);
            this->close();
        }

        break;
    }
    default:
        break;
    }
}

TeacherProcessWindow::~TeacherProcessWindow()
{
    delete ui;
}

void TeacherProcessWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QWidget *clickedWidget = childAt(event->pos());

        if (clickedWidget == ui->Headar || ui->Headar->isAncestorOf(clickedWidget)) {
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }
}

void TeacherProcessWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QWidget *clickedWidget = childAt(event->pos());

        if (clickedWidget == ui->Headar || ui->Headar->isAncestorOf(clickedWidget)) {
            move(event->globalPos() - m_dragPosition);
            event->accept();
        }
    }
}

void TeacherProcessWindow::on_closeButton_clicked()
{
    this->close();
}


void TeacherProcessWindow::on_cancelButon_clicked()
{
    this->close();
}

void TeacherProcessWindow::validateTeacherData(const QString& PIB, const int postID){
    QRegularExpression regex(
        "^[\\p{L}]+(-[\\p{L}]+)*( [\\p{L}]+(-[\\p{L}]+)*){1,2}$"
        );

    if (!regex.match(PIB).hasMatch()) {
        throw std::runtime_error(
            "ПІБ має містити 2 або 3 слова (тільки літери, можна з дефісом)"
            );
    }

    if (postID <= -1) {
        throw std::runtime_error("Посада повинна бути обрана");
    }
}

TeacherData TeacherProcessWindow::getTeacherDataFromUI(){
    TeacherData data;

    data.PIB = ui->PIBLineEdit->text();
    data.postID = ui->postComboBox->currentData().toInt();
    data.rate = ui->rateLineEdit->text().toFloat();
    data.otherLoad = ui->otherLoadLineEdit->text().toInt();

    return data;
}

void TeacherProcessWindow::addTeacher(){
    try {
        TeacherData data = getTeacherDataFromUI();

        validateTeacherData(data.PIB, data.postID);

        dbManager->addTeacher(data);

        this->close();

    } catch (const std::exception &e) {
        ErrorHandler::showError(this, "Помилка введення", e);
    }
}

void TeacherProcessWindow::editTeacher(){
    try {
        TeacherData data = getTeacherDataFromUI();

        data.teacherID = this->property("teacherId").toInt();
        data.configYear = this->property("configYear").toInt();

        validateTeacherData(data.PIB, data.postID);

        dbManager->updateTeacher(data);

        this->close();

    } catch (const std::exception &e) {
        ErrorHandler::showError(this, "Помилка введення", e);
    }
}

void TeacherProcessWindow::on_agreeButton_clicked()
{
    switch (wT) {
    case WindowType::Adding:{
        addTeacher();
        break;
    }
    case WindowType::Editing:
        editTeacher();
        break;
    default:
        break;
    }
}