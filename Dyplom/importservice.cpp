#include "importservice.h"
#include <QSqlQuery>
#include <QDebug>
#define QT_NO_DEBUG_OUTPUT

ImportService::Result ImportService::process(const ImportWorkbookDto& workbook){
    qDebug() << "[ImportService::process(workbook)] start";

    Result result;

    for (const auto& sheet : workbook.sheets) {
        qDebug() << "[ImportService::process(workbook)] validating sheet:" << sheet.sheetName;
        validateSheet(sheet, result);
    }

    result.success = result.errors.isEmpty();

    qDebug() << "[ImportService::process(workbook)] done. success =" << result.success << ", errors =" << result.errors.size();

    return result;
}

void ImportService::validateHeader(const ImportSheetDto& sheet, Result& result){
    qDebug() << "[ImportService::validateHeader] sheet =" << sheet.sheetName;

    const auto& h = sheet.header;

    if (h.groupName.isEmpty()) {
        qDebug() << "[ImportService::validateHeader] error: groupName is empty";
        result.errors.append({sheet.sheetName, -1, "Не вказана група"});
    }
}

void ImportService::validateRow(const ImportSheetDto& sheet, const DisciplineRowDto& row, Result& result){
    qDebug() << "[ImportService::validateRow] sheet =" << sheet.sheetName << ", row =" << row.excelRow << ", discipline =" << row.disciplineName;

    if (row.disciplineName.isEmpty()) {
        qDebug() << "[ImportService::validateRow] error: empty disciplineName";
        result.errors.append({sheet.sheetName, row.excelRow, "Порожня назва дисципліни"});
    }

    if (row.semester <= 0) {
        qDebug() << "[ImportService::validateRow] error: invalid semester =" << row.semester;
        result.errors.append({sheet.sheetName, row.excelRow, "Некоректний семестр"});
    }

    if (row.lectures.isValid() && row.lectures.toInt() < 0) {
        qDebug() << "[ImportService::validateRow] error: lectures < 0 =" << row.lectures;
        result.errors.append({sheet.sheetName, row.excelRow, "Лекції < 0"});
    }
}

QList<DisciplineRowDto> ImportService::filterRowsByDepartment(const QList<DisciplineRowDto>& rows, const QString& department){
    qDebug() << "[ImportService::filterRowsByDepartment] start, target department =" << department << ", rows =" << rows.size();

    QList<DisciplineRowDto> filtered;

    for (const auto& row : rows) {
        qDebug() << "[ImportService::filterRowsByDepartment] checking row =" << row.excelRow << ", row department =" << row.departmentName;

        if (row.departmentName.trimmed().compare(department.trimmed(), Qt::CaseInsensitive) == 0) {
            //qDebug() << "[ImportService::filterRowsByDepartment] matched row =" << row.excelRow;
            filtered.append(row);
        }
    }

    qDebug() << "[ImportService::filterRowsByDepartment] done, filtered rows =" << filtered.size();
    return filtered;
}

ImportWorkbookDto ImportService::process(ImportWorkbookDto workbook, const QString& targetDepartment, Result& result){
    //qDebug() << "[ImportService::process(workbook, department)] start, targetDepartment =" << targetDepartment;

    for (auto& sheet : workbook.sheets) {
        qDebug() << "[ImportService::process(workbook, department)] processing sheet =" << sheet.sheetName;

        validateHeader(sheet, result);

        auto filteredRows = filterRowsByDepartment(sheet.rows, targetDepartment);

        if (filteredRows.isEmpty()) {
            qDebug() << "[ImportService::process(workbook, department)] no rows for department in sheet =" << sheet.sheetName;
            result.errors.append({
                sheet.sheetName,
                -1,
                "Немає даних для кафедри: " + targetDepartment
            });
        }

        for (const auto& row : filteredRows) {
            validateRow(sheet, row, result);
        }

        sheet.rows = filteredRows;

        qDebug() << "[ImportService::process(workbook, department)] sheet filtered, rows left =" << sheet.rows.size();
    }

    result.success = result.errors.isEmpty();

    qDebug() << "[ImportService::process(workbook, department)] done. success =" << result.success << ", errors =" << result.errors.size();

    return workbook;
}

void ImportService::validateSheet(const ImportSheetDto& sheet, Result& result){
    qDebug() << "[ImportService::validateSheet] start, sheet =" << sheet.sheetName;

    validateHeader(sheet, result);

    if (sheet.rows.isEmpty()) {
        qDebug() << "[ImportService::validateSheet] error: sheet has no rows";
        result.errors.append({
            sheet.sheetName,
            -1,
            "Лист не містить жодного рядка з дисциплінами"
        });
        return;
    }

    for (const auto& row : sheet.rows) {
        validateRow(sheet, row, result);
    }

    qDebug() << "[ImportService::validateSheet] done, sheet =" << sheet.sheetName;
}