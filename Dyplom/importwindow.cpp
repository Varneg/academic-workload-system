#include "importwindow.h"
#include "ui_importwindow.h"
#include <QFileDialog>
#include "exceltemplatereader.h"
#include "importservice.h"
#include "ErrorHandler.h"
#include "importexecutor.h"

ImportWindow::ImportWindow(QWidget *parent, int curentYear)
    : QDialog(parent)
    , ui(new Ui::ImportWindow)
{
    year = curentYear;
    ui->setupUi(this);
}

ImportWindow::~ImportWindow()
{
    delete ui;
}

void ImportWindow::on_chooseFilePushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Оберіть Excel файл",
        "",
        "Excel Files (*.xlsx *.xls);;All Files (*)"
        );

    if (!fileName.isEmpty()) {
        ui->chooseFileLineEdit->setText(fileName);
    }
}

void ImportWindow::on_cancelButon_clicked()
{
    this->close();
}

void ImportWindow::import(){
    try {
        ExcelTemplateReader reader;
        auto workbook = reader.read(ui->chooseFileLineEdit->text());

        ImportService service;
        ImportService::Result result;

        auto filteredWorkbook = service.process(workbook, ui->departmentLineEdit->text(), result);

        if (!result.success) {
            throw std::runtime_error("Validation error");
        }

        ImportExecutor executor;
        executor.execute(filteredWorkbook, year);
    } catch (const std::exception& e) {
        ErrorHandler::showError(this, "Помилка імпорту", e);
    }
}

void ImportWindow::on_agreeButton_clicked()
{
    import();
    this->close();
}