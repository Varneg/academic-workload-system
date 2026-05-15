#ifndef EXCELEXPORTER_H
#define EXCELEXPORTER_H

#include "exportdto.h"

class ExcelExporter
{
private:
    struct RowNavigator {
        int disciplineName = 5;
        int group = 8;
        int course = 9;
        int studentQuantiti = 10;
        int lection = 11;
        int practick = 12;
        int laborator = 13;
        int exam = 14;
        int consultationBeforExam = 15;
        int courseWork = 23;
    };

public:
    static void exportToFile(const ExportDto& dto, const QString& outputPath);
};

#endif // EXCELEXPORTER_H
