#include "exportservice.h"
#include "databasemanager.h"
#include <QMap>

ExportDto ExportService::buildExportData(int teacherId, int year)
{
    ExportDto dto;

    auto header = DatabaseManager::instance().getTeacherHeaderInfo(teacherId, year);
    dto.head.year = year;
    dto.head.pib = header.first;
    dto.head.rate = header.second;

    QSqlQuery query = DatabaseManager::instance().getExportTeacherLoad(teacherId, year);

    QMap<QString, int> disciplineIndex;

    while (query.next()) {
        int semester        = query.value("Semester").toInt();
        QString discipline  = query.value("DisciplineName").toString();
        int generalTime     = query.value("GeneralTime").toInt();
        int activityId      = query.value("ActivityID").toInt();
        QString speciality  = query.value("SpecialityName").toString();
        int students        = query.value("StudentsQuantity").toInt();

        if(activityId == 5)
            discipline = QString("Курсова робота «%1»").arg(discipline);

        QString key = QString("%1|%2|%3").arg(semester).arg(discipline).arg(speciality);

        if (!disciplineIndex.contains(key)) {
            DisciplineActivityDto item;
            item.semestr = semester;
            item.generalTime = generalTime;
            item.disciplineName = discipline;
            item.specialityName = speciality;
            item.quantitiStudent = students;

            dto.activity.append(item);
            disciplineIndex[key] = dto.activity.size() - 1;
        }

        ActivityInfo act;
        act.activityId = activityId;
        act.load = generalTime;
        act.studentCount = students;

        dto.activity[disciplineIndex[key]].activities.append(act);
    }

    return dto;
}