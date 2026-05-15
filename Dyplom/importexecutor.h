#ifndef IMPORTEXECUTOR_H
#define IMPORTEXECUTOR_H

#include "ImportDto.h"
#include "databasemanager.h"

class ImportExecutor
{
public:
    void execute(const ImportWorkbookDto& workbook, int year);

private:
    DatabaseManager* dbManager;
    QList<ActivityLoadDto> extractActivities(const DisciplineRowDto& row, int studentCount);
    void appendIfValid(QList<ActivityLoadDto>& result, const DisciplineRowDto& row, const QVariant& value, int activityId);
    void appendLabs(QList<ActivityLoadDto>& result, const DisciplineRowDto& row, int studentCount);
};

#endif // IMPORTEXECUTOR_H
