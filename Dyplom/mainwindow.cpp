#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QSqlQueryModel>

#include "uiUtils.h"
#include "teacherprocesswindow.h"
#include "settingyearwindow.h"
#include "disciplineprocesswindow.h"
#include "groupprocesswindow.h"
#include "specialityprocesswindow.h"
#include "ErrorHandler.h"
#include "importwindow.h"
#include "exportwindow.h"

void MainWindow::resizeFooter(){
    QWidget *w = ui->footerStack->currentWidget();
    if (w) {
        ui->footerStack->setFixedSize(w->sizeHint());
    }
}

void MainWindow::changeFooterPage(int index){
    ui->footerStack->setCurrentIndex(qBound(0, index, ui->footerStack->count() - 1));

    index = qBound(0, index, ui->footerStack->count() - 1);
    ui->footerStack->setCurrentIndex(index);

    resizeFooter();
}

void MainWindow::initDatabase() {
    bool connected = false;

    while (!connected) {
        try {
            dbManager->instance();
            connected = true;
        }
        catch (const std::exception& e) {
            ErrorHandler::showError(this, "Не вдалося підєднатися до БД", e);
            auto reply = QMessageBox::question(this, "Помилка", "Повторити спробу? При відхиленні программа буде закрита!", QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                continue;
            } else {
                QApplication::quit();
                exit(0);
            }
        }
    }
}

void MainWindow::fillConfigYearComboBox(){
    try{
        QSqlQuery query = dbManager->getEnumConfig();

        ui->configYearComboBox->clear();

        while(query.next()){
            ui->configYearComboBox->addItem(query.value("ConfigYear").toString() + " / " + QString::number(query.value("ConfigYear").toInt() + 1));
        }

        ui->configYearComboBox->setCurrentIndex(ui->configYearComboBox->count() - 1);
    }catch (const std::exception& e){
        ErrorHandler::showError(this, "Помилка запиту до БД", e);
    }
}

void MainWindow::setConfig(int year){
    try {
        QSqlQuery query = dbManager->getYearConfig(year);

        query.next();

        currentConfig.currentYear = query.value("ConfigYear").toInt();
        currentConfig.anualLoad = query.value("AnualLoad").toInt();
        currentConfig.weakLoad = query.value("WeakLoad").toInt();
        currentConfig.badImbalance = query.value("BadImbalance").toInt();
        currentConfig.criticalImbalance = query.value("CriticalImbalance").toInt();

    } catch (const std::exception& e) {
        ErrorHandler::showError(this, "Помилка запиту до БД", e);
    }
}

QStandardItem* MainWindow::makeItem(const QVariant &value) {
    auto *item = new QStandardItem();

    if (value.isNull())
        item->setText("-");
    else
        item->setText(value.toString());

    item->setTextAlignment(Qt::AlignCenter);

    return item;
}

void MainWindow::setupTableView(QTableView *tableView, int hidenColumn)
{
    tableView->verticalHeader()->setVisible(false);
    tableView->verticalHeader()->setDefaultSectionSize(50);

    if(hidenColumn >= 0 && hidenColumn < tableView->model()->columnCount())
        tableView->setColumnHidden(hidenColumn, true);

    tableView->setWordWrap(true);

    auto *header = tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    header->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tableView->setStyleSheet(UiUtils::readStyleFile(this, TABLE_VIEW_STYLE_FILE));

    tableView->horizontalHeader()->setDefaultAlignment(Qt::Alignment(Qt::AlignCenter | Qt::TextWordWrap));

    tableView->horizontalHeader()->setMinimumHeight(80);

    tableView->setSortingEnabled(true);
    tableView->sortByColumn(0, Qt::AscendingOrder);

    tableView->setAlternatingRowColors(true);
}

void MainWindow::setAllDelegatesMode(ActionMode mode)
{
    for (auto delegate : m_delegates) {
        delegate->setMode(mode);
    }

    ui->teacherTableView->viewport()->update();
    ui->disciplineTableView->viewport()->update();
    ui->groupTabelView->viewport()->update();
    ui->specialityTableView->viewport()->update();
}

void MainWindow::setupDelegate(QTableView *tableView, QStandardItemModel* model, int column, TableType type){
    auto *delegate = new ButtonDelegate(type, this);
    m_delegates[type] = delegate;
    tableView->setItemDelegateForColumn(column, delegate);

    // EDIT
    connect(delegate, &ButtonDelegate::editClicked, this, [this](int id, TableType type) {

        if (type == TableType::Teacher){
            TeacherProcessWindow popUp(nullptr, WindowType::Editing, id, currentConfig.currentYear);
            popUp.setModal(true);
            popUp.exec();
            updateTableOnPage(0);
        }
        else if (type == TableType::Discipline){
            DisciplineProcessWindow popUp(nullptr, WindowType::Editing, currentConfig.currentYear, id);
            popUp.setModal(true);
            popUp.exec();
            updateTableOnPage(1);
        }
        else if (type == TableType::Speciality){
            SpecialityProcessWindow popUp(nullptr, WindowType::Editing, id);
            popUp.setModal(true);
            popUp.exec();
            updateTableOnPage(2);
        }
        else if (type == TableType::Group) {
            GroupProcessWindow popUp(nullptr, WindowType::Editing, currentConfig.currentYear, id);
            popUp.setModal(true);
            popUp.exec();
            updateTableOnPage(2);
        }
    });

    // DELETE
    connect(delegate, &ButtonDelegate::deleteClicked, this, [this](int id, TableType type) {
        if (QMessageBox::question(this, "Підтвердження","Видалити запис?") == QMessageBox::Yes){
            try {
                if (type == TableType::Teacher){
                    dbManager->deleteTeacher(id);
                    updateTableOnPage(0);
                }
                else if (type == TableType::Discipline){
                    dbManager->deleteDisciplineActivity(id);
                    updateTableOnPage(1);
                }
                else if (type == TableType::Speciality){
                    dbManager->deleteSpeciality(id);
                    updateTableOnPage(2);
                }
                else if (type == TableType::Group) {
                    dbManager->deleteGroup(id);
                    updateTableOnPage(2);
                }
            } catch (const std::exception &e) {
                ErrorHandler::showError(this, "Помилка видалення", e);
            }

            //refreshTables();
        }
    });

    tableView->setItemDelegateForColumn(column, delegate);
}

void MainWindow::writeTeacherData(){
    try {
        QSqlQuery query = dbManager->getTeacherData(currentConfig.currentYear);

        QStandardItemModel *model = new QStandardItemModel(this);
        model->setColumnCount(11);

        model->setHeaderData(0, Qt::Horizontal, "ID");
        model->setHeaderData(1, Qt::Horizontal, "ПІБ");
        model->setHeaderData(2, Qt::Horizontal, "1 семестр");
        model->setHeaderData(3, Qt::Horizontal, "2 семестр");
        model->setHeaderData(4, Qt::Horizontal, "Інше навантаження");
        model->setHeaderData(5, Qt::Horizontal, "Загальна навантаження");
        model->setHeaderData(6, Qt::Horizontal, "Допустиме навантаження");
        model->setHeaderData(7, Qt::Horizontal, "Ставка");
        model->setHeaderData(8, Qt::Horizontal, "Посада");
        model->setHeaderData(9, Qt::Horizontal, "Тижневе навантаження");
        model->setHeaderData(10, Qt::Horizontal, "Редагувати");

        int row = 0;

        while (query.next()) {
            model->insertRow(row);

            model->setItem(row, 0, makeItem(query.value(0)));
            model->setItem(row, 1, new QStandardItem(query.value(1).toString()));
            model->setItem(row, 2, makeItem(query.value(2)));
            model->setItem(row, 3, makeItem(query.value(3)));

            double sem1 = query.value(2).toDouble();
            double sem2 = query.value(3).toDouble();

            QStandardItem* sem1Item = makeItem(sem1);
            QStandardItem* sem2Item = makeItem(sem2);

            double diff = std::abs(sem1 - sem2);
            QStandardItem* biggerItem = (sem1 > sem2) ? sem1Item : sem2Item;

            if (diff > currentConfig.criticalImbalance) {
                biggerItem->setBackground(QBrush(QColor(226, 53, 0)));
            }
            else if (diff > currentConfig.badImbalance) {
                biggerItem->setBackground(QBrush(QColor(255, 227, 69)));
            }

            model->setItem(row, 2, sem1Item);
            model->setItem(row, 3, sem2Item);

            model->setItem(row, 4, makeItem(query.value(4)));

            double rate = query.value(6).toDouble();
            double allowedLoad = rate * currentConfig.anualLoad;
            double totalLoad = query.value(5).toDouble();

            QStandardItem* totalItem = makeItem(totalLoad);
            QStandardItem* allowedItem = makeItem(QString::number(allowedLoad));

            if (totalLoad > allowedLoad) {
                totalItem->setBackground(QBrush(QColor(226, 53, 0)));
            }
            else if (totalLoad < allowedLoad) {
                totalItem->setBackground(QBrush(QColor(255, 227, 69)));
            }

            model->setItem(row, 5, totalItem);
            model->setItem(row, 6, allowedItem);

            model->setItem(row, 7, makeItem(query.value(6)));
            model->setItem(row, 8, makeItem(query.value(7)));

            double weeklyLoad = query.value(8).toDouble();

            QStandardItem* weeklyItem = makeItem(weeklyLoad);

            if (weeklyLoad > currentConfig.weakLoad) {
                weeklyItem->setBackground(QBrush(QColor(226, 53, 0)));
            }

            model->setItem(row, 9, weeklyItem);

            model->setItem(row, 10, new QStandardItem());


            row++;
        }

        teacherProxy = new QSortFilterProxyModel(this);
        teacherProxy->setSourceModel(model);
        teacherProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
        teacherProxy->setFilterKeyColumn(-1);

        ui->teacherTableView->setModel(teacherProxy);

        setupTableView(ui->teacherTableView, 0);
        setupDelegate(ui->teacherTableView, model, 10, TableType::Teacher);
    }
    catch (const std::exception &e) {
        ErrorHandler::showError(this, "Помилка запиту до БД", e);
    }
}

void MainWindow::writeLoadData(){
    try {
        QSqlQuery query = dbManager->getLoadData(currentConfig.currentYear);

        QStandardItemModel *model = new QStandardItemModel(this);
        model->setColumnCount(10);

        model->setHeaderData(0, Qt::Horizontal, "ID");
        model->setHeaderData(1, Qt::Horizontal, "Дисципліна");
        model->setHeaderData(2, Qt::Horizontal, "Тип");
        model->setHeaderData(3, Qt::Horizontal, "Група");
        model->setHeaderData(4, Qt::Horizontal, "Кількість годин на тиждень");
        model->setHeaderData(5, Qt::Horizontal, "Загальна кількість годин");
        model->setHeaderData(6, Qt::Horizontal, "Семестр");
        model->setHeaderData(7, Qt::Horizontal, "Кількість студентів");
        model->setHeaderData(8, Qt::Horizontal, "ПІБ викладача");
        model->setHeaderData(9, Qt::Horizontal, "Редагувати");

        int row = 0;

        while(query.next()){
            model->insertRow(row);

            model->setItem(row, 0, makeItem(query.value(0)));
            model->setItem(row, 1, new QStandardItem(query.value(1).toString()));
            model->setItem(row, 2, makeItem(query.value(2)));
            model->setItem(row, 3, makeItem(query.value(3)));
            model->setItem(row, 4, makeItem(query.value(4)));
            model->setItem(row, 5, makeItem(query.value(5)));
            model->setItem(row, 6, makeItem(query.value(6)));
            model->setItem(row, 7, makeItem(query.value(7)));
            model->setItem(row, 8, makeItem(query.value(8)));
            model->setItem(row, 9, new QStandardItem());

            row++;
        }

        disciplineProxy = new QSortFilterProxyModel(this);
        disciplineProxy->setSourceModel(model);
        disciplineProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
        disciplineProxy->setFilterKeyColumn(-1);

        ui->disciplineTableView->setModel(disciplineProxy);

        setupTableView(ui->disciplineTableView, 0);
        setupDelegate(ui->disciplineTableView, model, 9, TableType::Discipline);
    } catch (const std::exception &e) {
        ErrorHandler::showError(this, "Помилка запиту до БД", e);
    }
}

void MainWindow::writeGroupData(){
    try {
        QSqlQuery query = dbManager->getGroupData(currentConfig.currentYear);

        QStandardItemModel *model = new QStandardItemModel(this);
        model->setColumnCount(6);

        model->setHeaderData(0, Qt::Horizontal, "ID");
        model->setHeaderData(1, Qt::Horizontal, "Спеціальність");
        model->setHeaderData(2, Qt::Horizontal, "Рік");
        model->setHeaderData(3, Qt::Horizontal, "Підгрупа");
        model->setHeaderData(4, Qt::Horizontal, "Кількість студентів");
        model->setHeaderData(5, Qt::Horizontal, "");

        int row = 0;

        while(query.next()){
            model->insertRow(row);

            model->setItem(row, 0, makeItem(query.value(0)));
            model->setItem(row, 1, new QStandardItem(query.value(1).toString()));
            model->setItem(row, 2, makeItem(query.value(2)));
            model->setItem(row, 3, makeItem(query.value(3)));
            model->setItem(row, 4, makeItem(query.value(4)));
            model->setItem(row, 5, new QStandardItem());

            row++;
        }

        groupProxy = new QSortFilterProxyModel(this);
        groupProxy->setSourceModel(model);
        groupProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
        groupProxy->setFilterKeyColumn(-1);

        ui->groupTabelView->setModel(groupProxy);

        setupTableView(ui->groupTabelView, 0);
        setupDelegate(ui->groupTabelView, model, 5, TableType::Group);
    } catch (const std::exception &e) {
        ErrorHandler::showError(this, "Помилка запиту до БД", e);
    }
}

void MainWindow::writeSpecialityData(){
    try {
        QSqlQuery query = dbManager->getSpecialityData();

        QStandardItemModel *model = new QStandardItemModel(this);
        model->setColumnCount(4);

        model->setHeaderData(0, Qt::Horizontal, "Номер спеціальності");
        model->setHeaderData(1, Qt::Horizontal, "Кафедра");
        model->setHeaderData(2, Qt::Horizontal, "Назва спеціальності");
        model->setHeaderData(3, Qt::Horizontal, "");

        int row = 0;

        while(query.next()){
            model->insertRow(row);

            model->setItem(row, 0, makeItem(query.value(0)));
            model->setItem(row, 1, new QStandardItem(query.value(1).toString()));
            model->setItem(row, 2, makeItem(query.value(2)));
            model->setItem(row, 3, new QStandardItem());

            row++;
        }

        ui->specialityTableView->setModel(model);

        setupTableView(ui->specialityTableView, 0);
        setupDelegate(ui->specialityTableView, model, 3, TableType::Speciality);
    } catch (const std::exception &e) {
        ErrorHandler::showError(this, "Помилка запиту до БД", e);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initDatabase();

    ui->tabWidget->setStyleSheet(UiUtils::readStyleFile(this, TAB_WIDGET_STYLE_FILE));
    UiUtils::setStandardButtonStyle(this, UiUtils::readStyleFile(this, BUTON_STYLE_FILE));
    UiUtils::setShadowOnAllPushButtons(this);

    UiUtils::setIconOnButton(":/res/img/excel.svg", ui->exportButton);
    //UiUtils::setIconOnButton(":/res/img/back-arrow.svg", ui->undoButton);
    ui->undoButton->hide(); // to do

    UiUtils::setIconOnButton(":/res/img/search.svg", ui->searchTeacherButton);
    UiUtils::setIconOnButton(":/res/img/search.svg", ui->searchDisciplineButton);
    UiUtils::setIconOnButton(":/res/img/search.svg", ui->searchGroupOrDepartmentButton);
    UiUtils::setIconOnButton(":/res/img/plus.svg", ui->addTeacherButton);
    UiUtils::setIconOnButton(":/res/img/trashcan.svg",ui->deleatButton);
    UiUtils::setIconOnButton(":/res/img/cogwheel.svg", ui->setteningButton);
    UiUtils::setIconOnButton(":/res/img/plus.svg", ui->addGroupButton);
    UiUtils::setIconOnButton(":/res/img/plus.svg", ui->addSpecialityButton);
    UiUtils::setIconOnButton(":/res/img/plus.svg", ui->addDisciplineButton);

    ui->tabWidget->setCurrentIndex(0);
    changeFooterPage(ui->tabWidget->currentIndex());
    fillConfigYearComboBox();

    ui->searchTeacherLineEdit->setPlaceholderText("Пошук...");
    ui->searchDisciplineLineEdit->setPlaceholderText("Пошук...");
    ui->searchGroupSpecialityLineEdit->setPlaceholderText("Пошук...");

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::changeFooterPage);

    connect(ui->searchTeacherLineEdit, &QLineEdit::textChanged,
            this, [this](const QString& text){
                if (teacherProxy)
                    teacherProxy->setFilterRegularExpression(
                        QRegularExpression(text, QRegularExpression::CaseInsensitiveOption)
                        );
            });

    connect(ui->searchDisciplineLineEdit, &QLineEdit::textChanged,
            this, [this](const QString& text){
                if (disciplineProxy)
                    disciplineProxy->setFilterRegularExpression(
                        QRegularExpression(text, QRegularExpression::CaseInsensitiveOption)
                        );
            });

    connect(ui->searchGroupSpecialityLineEdit, &QLineEdit::textChanged,
            this, [this](const QString& text){
                if (groupProxy)
                    groupProxy->setFilterRegularExpression(
                        QRegularExpression(text, QRegularExpression::CaseInsensitiveOption)
                        );
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addTeacherButton_clicked()
{
    TeacherProcessWindow popUp(nullptr, WindowType::Adding);
    popUp.setModal(true);
    popUp.exec();
    updateTableOnPage(0);
}


void MainWindow::on_addNewYearButton_clicked()
{
    SettingYearWindow popUp(nullptr, WindowType::Adding);
    popUp.setModal(true);
    popUp.exec();
    fillConfigYearComboBox();
}


void MainWindow::on_setteningButton_clicked()
{
    SettingYearWindow popUp(nullptr, WindowType::Editing, currentConfig.currentYear);
    popUp.setModal(true);
    popUp.exec();
    fillConfigYearComboBox();
}


void MainWindow::on_addDisciplineButton_clicked()
{
    DisciplineProcessWindow popUp(nullptr, WindowType::Adding, currentConfig.currentYear);
    popUp.setModal(true);
    popUp.exec();
    updateTableOnPage(1);
}


void MainWindow::on_addGroupButton_clicked()
{
    GroupProcessWindow popUp(nullptr, WindowType::Adding, currentConfig.currentYear);
    popUp.setModal(true);
    popUp.exec();
    updateTableOnPage(2);
}


void MainWindow::on_addSpecialityButton_clicked()
{
    SpecialityProcessWindow popUp(nullptr, WindowType::Adding);
    popUp.setModal(true);
    popUp.exec();
    updateTableOnPage(2);
}

void MainWindow::on_configYearComboBox_currentIndexChanged(int index)
{
    setConfig(ui->configYearComboBox->currentText().left(4).toInt());
    writeTeacherData();

    updateTableOnPage(ui->tabWidget->currentIndex());
}

void MainWindow::on_deleatButton_clicked()
{
    m_deleteMode = !m_deleteMode;

    ActionMode mode = m_deleteMode ? ActionMode::Delete : ActionMode::Edit;

    for (auto delegate : m_delegates) {
        delegate->setMode(mode);
    }

    ui->teacherTableView->viewport()->update();
    ui->disciplineTableView->viewport()->update();
    ui->groupTabelView->viewport()->update();
    ui->specialityTableView->viewport()->update();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    updateTableOnPage(index);
}

void MainWindow::updateTableOnPage(int index){
    switch (index) {
    case 0:
    {
        writeTeacherData();
        if (teacherProxy)
            teacherProxy->setFilterRegularExpression(QRegularExpression(ui->searchTeacherLineEdit->text(), QRegularExpression::CaseInsensitiveOption));
        break;
    }

    case 1:
    {
        writeLoadData();
        if (disciplineProxy)
            disciplineProxy->setFilterRegularExpression(QRegularExpression(ui->searchDisciplineLineEdit->text(), QRegularExpression::CaseInsensitiveOption));
        break;
    }

    case 2:
    {
        writeGroupData();
        writeSpecialityData();
        if (groupProxy)
            groupProxy->setFilterRegularExpression(QRegularExpression(ui->searchGroupSpecialityLineEdit->text(), QRegularExpression::CaseInsensitiveOption));
        break;
    }

    default:
        break;
    }
}

void MainWindow::on_importButton_clicked()
{
    ImportWindow popUp(nullptr, currentConfig.currentYear);
    popUp.setModal(true);
    popUp.exec();
    updateTableOnPage(ui->tabWidget->currentIndex());
}


void MainWindow::on_exportButton_clicked()
{
    exportwindow popUp(nullptr, currentConfig.currentYear);
    popUp.setModal(true);
    popUp.exec();
    updateTableOnPage(ui->tabWidget->currentIndex());
}

