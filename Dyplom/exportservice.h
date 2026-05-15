#ifndef EXPORTSERVICE_H
#define EXPORTSERVICE_H

#include "exportdto.h"

class ExportService
{
public:
    static ExportDto buildExportData(int teacherId, int year);
};

#endif // EXPORTSERVICE_H
