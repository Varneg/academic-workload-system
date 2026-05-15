#include "ImportExecutor.h"
#include "databasemanager.h"
#include <stdexcept>
#include <cmath>
#include "datamodels.h"

void ImportExecutor::execute(const ImportWorkbookDto& workbook, int year)
{
    try {
        dbManager->instance();
    } catch (const std::exception& e) {
        throw std::runtime_error("Не вдалося підєднатися до БД");
    }


    QSqlDatabase database = QSqlDatabase::database();

    if (!database.transaction()) {
        throw std::runtime_error("Не вдалося почати транзакцію");
    }

    try {
        for (const auto& sheet : workbook.sheets) {

            if (sheet.rows.isEmpty())
                continue;

            const QString& departmentName = sheet.rows[0].departmentName;

            int departmentID = dbManager->getOrCreateDepartment(departmentName);
            dbManager->getOrCreateSpeciality(sheet.header.groupName, sheet.header.specialityNumber, departmentID);
            int *groupID = dbManager->getOrCreateGroup(sheet.header.specialityNumber, sheet.header.groupYear, sheet.header.groupCount, year, sheet.header.studentCount);

            for (const auto& row : sheet.rows) {
                int disciplineID = dbManager->getOrCreateDiscipline(row.disciplineName);

                const QList<ActivityLoadDto> activities = extractActivities(row, sheet.header.studentCount);

                for (const auto& activity : activities) {
                    const bool isGroupLoad = dbManager->isGroupActivity(activity.activityId);

                    if (!isGroupLoad) {
                        DisciplineActivityData data;

                        data.disciplineID = disciplineID;
                        data.disciplineTypeID = activity.activityId;
                        data.groupID = groupID[0];
                        data.teacherID = 0;

                        data.totalHour = activity.hours;
                        data.hourPerWeek = activity.weekLoad;
                        data.semestr = row.semester;
                        data.quantityStudent = activity.quantityStudent;
                        data.currentYear = year;

                        dbManager->addDisciplineActivity(data);

                        continue;
                    }

                    for (int i = 0; i < sheet.header.groupCount; ++i) {
                        DisciplineActivityData data;

                        data.disciplineID = disciplineID;
                        data.disciplineTypeID = activity.activityId;
                        data.groupID = groupID[i];
                        data.teacherID = 0;

                        data.totalHour = activity.hours;
                        data.hourPerWeek = activity.weekLoad;
                        data.semestr = row.semester;
                        data.quantityStudent = activity.quantityStudent;
                        data.currentYear = year;

                        dbManager->addDisciplineActivity(data);
                    }
                }
            }

            delete [] groupID;
        }


        if (!database.commit()) {
            throw std::runtime_error("Невдалося импортувати дані");
        }

    } catch (...) {
        database.rollback();
        throw;
    }
}

void ImportExecutor::appendIfValid(QList<ActivityLoadDto>& result, const DisciplineRowDto& row, const QVariant& value, int activityId) {
    if (!value.isValid())
        return;

    QString text = value.toString().trimmed();
    if (text.isEmpty())
        return;

    bool ok = false;
    float weekLoad = text.replace(",", ".").toFloat(&ok);

    if (!ok || weekLoad <= 0.0)
        return;

    const float annualLoad = weekLoad * row.weeks;

    result.append({activityId, annualLoad, weekLoad, -1 });
};

void ImportExecutor::appendLabs( QList<ActivityLoadDto>& result, const DisciplineRowDto& row, int studentCount){
    if (!row.labs.isValid())
        return;

    QString text = row.labs.toString().trimmed();
    bool ok = false;
    float weekLoad = text.replace(",", ".").toFloat(&ok);

    if (!ok || weekLoad <= 0.0)
        return;

    const float annualLoad = weekLoad * row.weeks;

    int totalStudents = studentCount;
    int parts = std::ceil(totalStudents / 15.0);

    if (parts <= 0)
        parts = 1;

    int base = totalStudents / parts;
    int remainder = totalStudents % parts;

    for (int i = 0; i < parts; ++i) {
        int qty = base + (i == parts - 1 ? remainder : 0);

        result.append({2, annualLoad, weekLoad, qty});
    }
}

QList<ActivityLoadDto> ImportExecutor::extractActivities(const DisciplineRowDto& row, int studentCount){
    QList<ActivityLoadDto> result;

    appendIfValid(result, row, row.lectures, 1);
    appendLabs(result, row, studentCount);
    appendIfValid(result, row, row.practice, 3);

    if (row.exams.isValid() && row.exams.toInt() > 0) {
        float hours = std::round(static_cast<float>(studentCount) / 4.0) + 2; // 4 - 15 minutes per one student; 2 - consultations before exams
        result.append({4, hours, -1, -1});
    }

    return result;
}