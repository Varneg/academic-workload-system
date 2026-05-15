#include "exportwindow.h"
#include "ui_exportwindow.h"
#include "ErrorHandler.h"
#include <QFileDialog>

#include "exportdto.h"
#include "exportservice.h"
#include "excelexporter.h"

exportwindow::exportwindow(QWidget *parent, int configYear)
    : QDialog(parent)
    , ui(new Ui::exportwindow)
{
    ui->setupUi(this);
    year = configYear;

    try {
        dbManager->instance();
    } catch (const std::exception& e) {
        ErrorHandler::showError(this, "Не вдалося підєднатися до БД", e);
        this->close();
    }

    ui->teacherComboBox->setDbHandlers(
        [this]() { return dbManager->getAllTeacherPIB(); }
        );
}

exportwindow::~exportwindow()
{
    delete ui;
}

void exportwindow::on_chooseFilePushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Зберегти Excel файл",
        "",
        "Excel Files (*.xlsx);;All Files (*)"
        );

    if (!fileName.isEmpty()) {
        if (!fileName.endsWith(".xlsx", Qt::CaseInsensitive)) {
            fileName += ".xlsx";
        }

        ui->chooseFileLineEdit->setText(fileName);
    }
}


void exportwindow::on_agreeButton_clicked()
{
    try {
        int teacherId = ui->teacherComboBox->currentData().toInt();
        QString path = ui->chooseFileLineEdit->text();

        if (path.isEmpty())
            throw std::runtime_error("EMPTY_EXPORT_PATH");

        ExportDto dto = ExportService::buildExportData(teacherId, year);
        ExcelExporter::exportToFile(dto, path);

        QMessageBox::information(this, "Успіх", "Файл успішно експортовано.");
    }
    catch (const std::exception& e) {
        ErrorHandler::showError(this, "Не вдалося експортувати файл", e);
    }
}

