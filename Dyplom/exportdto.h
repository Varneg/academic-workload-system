#ifndef EXPORTDTO_H
#define EXPORTDTO_H

#include <QList>

struct headerData{
    int year;
    QString pib;
    int rate;
};

struct ActivityInfo {
    int activityId;
    int load; // if 0, there is no given activity
    int studentCount;
};

struct DisciplineActivityDto{
    int semestr;
    int generalTime;
    QString disciplineName;
    QList<ActivityInfo> activities;
    QString specialityName;
    int quantitiStudent;
};

struct ExportDto{
    headerData head;
    QList<DisciplineActivityDto> activity;
};

#endif // EXPORTDTO_H
