#ifndef IMPORTDTO_H
#define IMPORTDTO_H

#include <QString>
#include <QList>
#include <QVariant>

//structures are used for import
struct GroupHeaderDto {
    int specialityNumber = 0;
    QString groupName;
    int studentCount = 0;
    int groupCount = 0;
    int groupYear = 0;
};

struct DisciplineRowDto {
    int excelRow = 0;

    QString disciplineName;
    QString departmentName;

    QVariant lectures;
    QVariant labs;
    QVariant practice;
    QVariant exams;
    //QVariant courseProject;

    int semester = 0;
    int weeks = 0;
};

struct ActivityLoadDto {
    int activityId;
    float hours;
    float weekLoad;
    int quantityStudent;
};

struct ImportSheetDto {
    QString sheetName;
    GroupHeaderDto header;
    QList<DisciplineRowDto> rows;
};

struct ImportWorkbookDto {
    QList<ImportSheetDto> sheets;
};

#endif // IMPORTDTO_H
