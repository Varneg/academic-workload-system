#ifndef DATAMODELS_H
#define DATAMODELS_H
#include <QString>

struct TeacherData
{
    QString PIB;
    int postID = -1;
    float rate = 0.0f;
    int otherLoad = 0;

    // for update
    int teacherID = -1;
    int configYear = -1;
};

struct DisciplineActivityData
{
    int disciplineID = -1;
    int disciplineTypeID = -1;
    int groupID = -1;
    int teacherID = -1;
    int totalHour = 0;
    float hourPerWeek = 0.0f;
    int semestr = 0;
    int quantityStudent = 0;
    int currentYear = 0;

    // for update
    int disciplineActivityID = -1;
};

struct GroupData
{
    int specialityNumber = -1;
    int groupYear = 0;
    int subgroup = 0;
    int quantityStudent = 0;
    int configYear = 0;

    // for update
    int studentGroupID = -1;
};

struct YearConfigData
{
    int configYear = -1;
    int anualLoad = 0;
    int weakLoad = 0;
    int badImbalance = 0;
    int criticalImbalance = 0;

    // for update
    int newConfigYear = -1;
};

#endif // DATAMODELS_H
