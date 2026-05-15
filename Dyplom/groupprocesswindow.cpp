#include "groupprocesswindow.h"
#include "ui_groupprocesswindow.h"
#include <QMouseEvent>
#include <QPoint>
#include "comboboxeditdelegate.h"
#include "ErrorHandler.h"
#include <QIntValidator>

void GroupProcessWindow::validation(){
    ui->subgroupLineEdit->setValidator(new QIntValidator(1, 10));
    ui->quantityStedentLineEdit->setValidator(new QIntValidator(0, 100));
    ui->yearLineEdit->setValidator(new QIntValidator(1900, 3000));
}

GroupProcessWindow::GroupProcessWindow(QWidget *parent, enum WindowType winType, int year, int id)
    : QDialog(parent)
    , ui(new Ui::GroupProcessWindow)
{
    ui->setupUi(this);
    wT = winType;
    configYear = year;

    this->setWindowFlags(Qt::FramelessWindowHint);
    UiUtils::setIconOnButton(":/res/img/close.svg", ui->closeButton);

    ui->yearLineEdit->setPlaceholderText("Введіть рік групи");
    ui->subgroupLineEdit->setPlaceholderText("Введіть номер підгрупи");
    ui->quantityStedentLineEdit->setPlaceholderText("Введіть кількість студентів");
    ui->specialityComboBox->lineEdit()->setPlaceholderText("Оберіть спеціальність");

    try {
        dbManager = &DatabaseManager::instance();
    } catch (const std::exception& e) {
        ErrorHandler::showError(this, "Не вдалося підєднатися до БД", e);
        this->close();
    }

    try{
        ui->specialityComboBox->setDbHandlers(
            [this]() { return dbManager->getSpecialityName(); }
            );
    }catch(const std::exception& e){
        ErrorHandler::showError(this, "Не вдалося отримати дані з БД", e);
        this->close();
    }

    validation();

    switch (wT) {
    case WindowType::Adding:
    {
        ui->windowTitle->setText("Додати групу");
        ui->agreeButton->setText("Додати");

        break;
    }
    case WindowType::Editing:
    {
        this->setProperty("groupID", id);

        ui->windowTitle->setText("Редагування групу");
        ui->agreeButton->setText("Зберігти");

        try {
            QSqlQuery query = dbManager->getGroupByID(id, configYear);

            if (!query.next()) {
                throw std::runtime_error("Групу не знайдено або запит повернув 0 рядків");
            }

            ui->specialityComboBox->setCurrentIndex(ui->specialityComboBox->findData(query.value(0).toInt()));
            ui->yearLineEdit->setText(query.value(1).toString());
            ui->subgroupLineEdit->setText(query.value(2).toString());
            ui->quantityStedentLineEdit->setText(query.value(3).toInt() <= 0 ? "" : query.value(3).toString());
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

GroupProcessWindow::~GroupProcessWindow()
{
    delete ui;
}

void GroupProcessWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QWidget *clickedWidget = childAt(event->pos());

        if (clickedWidget == ui->Headar || ui->Headar->isAncestorOf(clickedWidget)) {
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }
}

void GroupProcessWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QWidget *clickedWidget = childAt(event->pos());

        if (clickedWidget == ui->Headar || ui->Headar->isAncestorOf(clickedWidget)) {
            move(event->globalPos() - m_dragPosition);
            event->accept();
        }
    }
}

void GroupProcessWindow::on_closeButton_clicked()
{
    this->close();
}


void GroupProcessWindow::on_cancelButon_clicked()
{
    this->close();
}

void GroupProcessWindow::validateGroupData(GroupData data){
    if(data.specialityNumber == -1 || data.groupYear == -1)
        throw std::runtime_error("Введіть усі обов'язкові дані");
}

GroupData GroupProcessWindow::getGroupDataFromUI(){
    GroupData data;

    data.specialityNumber = UiUtils::parseOrMinusOne(ui->specialityComboBox->currentData().toInt());
    data.groupYear = UiUtils::parseOrMinusOne(ui->yearLineEdit->text().toInt());
    data.subgroup = UiUtils::parseOrMinusOne(ui->subgroupLineEdit->text().toInt());
    data.quantityStudent = UiUtils::parseOrMinusOne(ui->quantityStedentLineEdit->text().toInt());
    data.configYear = configYear;

    validateGroupData(data);

    return data;
}

void GroupProcessWindow::addGroup(){
    try {
        GroupData data = getGroupDataFromUI();

        dbManager->addGroup(data);
    } catch (const std::exception &e) {
        ErrorHandler::showError(this, "Помилка введення", e);
    }
}

void GroupProcessWindow::editGroup(){
    try {
        GroupData data = getGroupDataFromUI();

        data.studentGroupID = this->property("groupID").toInt();

        dbManager->updateGroup(data);
    } catch (const std::exception &e) {
        ErrorHandler::showError(this, "Помилка введення", e);
    }
}

void GroupProcessWindow::on_agreeButton_clicked()
{
    switch (wT) {
    case WindowType::Adding:
    {
        addGroup();
        this->close();
        break;
    }
    case WindowType::Editing:
    {
        editGroup();
        this->close();
        break;
    }
    default:
        break;
    }
}