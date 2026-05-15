#ifndef EXCELTEMPLATEREADER_H
#define EXCELTEMPLATEREADER_H

#include "ImportDto.h"

namespace QXlsx {
class Document;
}

class ExcelTemplateReader
{
public:
    ImportWorkbookDto read(const QString& filePath);

private:
    ImportSheetDto readSheet(QXlsx::Document& doc, const QString& sheetName);
    GroupHeaderDto readHeader(QXlsx::Document& doc);
    QList<DisciplineRowDto> readRows(QXlsx::Document& doc);
};

#endif // EXCELTEMPLATEREADER_H