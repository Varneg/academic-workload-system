#ifndef IMPORTSERVICE_H
#define IMPORTSERVICE_H

#include "ImportDto.h"
#include <QStringList>

class ImportService //class implementing validation
{
public:
    struct ValidationError {
        QString sheet;
        int row = -1;      // -1 = error on header
        QString message;
    };

    struct Result {
        bool success = true;
        QList<ValidationError> errors;
    };

    Result process(const ImportWorkbookDto& workbook);
    ImportWorkbookDto process(ImportWorkbookDto workbook, const QString& targetDepartment, Result& result);

private:
    void validateSheet(const ImportSheetDto& sheet, Result& result);
    void validateHeader(const ImportSheetDto& sheet, Result& result);
    void validateRow(const ImportSheetDto& sheet, const DisciplineRowDto& row, Result& result);
    QList<DisciplineRowDto> filterRowsByDepartment(const QList<DisciplineRowDto>& rows, const QString& department);
};

#endif // IMPORTSERVICE_H
