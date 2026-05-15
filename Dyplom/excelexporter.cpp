#include "excelexporter.h"

#include <QFile>
#include <QDir>
#include <stdexcept>
#include <QDebug>

#include "xlsxdocument.h"
using namespace QXlsx;

void ExcelExporter::exportToFile(const ExportDto& dto, const QString& outputPath)
{
    QString templatePath = ":/template/excelTemplate/Форма 3.xlsx";

    QFileInfo fi(outputPath);
    QDir().mkpath(fi.path());

    if (QFile::exists(outputPath)) {
        if (!QFile::remove(outputPath)) {
            qDebug() << "Failed to remove existing file:" << outputPath;
        }
    }
    Document xlsx(templatePath);

    if (!xlsx.load()) {
        qDebug() << "Failed to load template:" << templatePath;
        throw std::runtime_error("FAILED_LOAD_TEMPLATE");
    }

    qDebug() << "Sheets:" << xlsx.sheetNames();

    QString targetSheet = "Лист 1";

    if (!xlsx.sheetNames().contains(targetSheet)) {
        qDebug() << "Available sheets:" << xlsx.sheetNames();
        throw std::runtime_error("SHEET_NOT_FOUND");
    }

    if (!xlsx.selectSheet(targetSheet)) {
        qDebug() << "Failed to select sheet:" << targetSheet;
        throw std::runtime_error("FAILED_SELECT_SHEET");
    }

    xlsx.write("A3", QString("Розподіл навчального навантаження між викладачами кафедри комп'ютерних наук та інформаційних технологій (ККН) на %1-%2 навчальний рік")
                                             .arg(dto.head.year)
                                             .arg(dto.head.year + 1));

    xlsx.write("B8", dto.head.pib);
    xlsx.write("B41", dto.head.pib);

    xlsx.write("D8", dto.head.rate);
    xlsx.write("D41", dto.head.rate);

    QString lastSemName[2];

    int currentRow[2] = {7, 40};
    int count[2] = {0, 0};

    RowNavigator rowNavigator;

    for (const auto& item : dto.activity) {
        int semIndex = (item.semestr % 2 != 0) ? 0 : 1;

        QString& lastName = lastSemName[semIndex];
        int& row = currentRow[semIndex];
        int& currentCount = count[semIndex];


        if (item.disciplineName != lastName) {

            if (currentCount >= 10)
                continue;

            row++;
            currentCount++;

            lastName = item.disciplineName;

            xlsx.write(row, rowNavigator.disciplineName, item.disciplineName);

            int course = (semIndex == 0) ? (item.semestr + 1) / 2 : item.semestr / 2;

            xlsx.write(row, rowNavigator.course, course);
            xlsx.write(row, rowNavigator.group, item.specialityName);
        }

        int maxStudents = 0;

        for (const auto& act : item.activities) {

            maxStudents = std::max(maxStudents, act.studentCount);

            int col = -1;

            switch (act.activityId) {
            case 1: col = rowNavigator.lection; break;
            case 2: col = rowNavigator.practick; break;
            case 3: col = rowNavigator.laborator; break;
            case 4: col = rowNavigator.exam; break;
            case 5: col = rowNavigator.courseWork; break;
            default: break;
            }

            if (col == -1)
                continue;

            QVariant oldVal = xlsx.read(row, col);

            int newVal = act.load;

            if (act.activityId == 4) {
                newVal -= 2;
                xlsx.write(row, rowNavigator.consultationBeforExam, 2);
            }

            if (oldVal.isValid())
                newVal += oldVal.toInt();

            xlsx.write(row, col, newVal);
        }

        QVariant oldStudents = xlsx.read(row, rowNavigator.studentQuantiti);

        if (!oldStudents.isValid() || oldStudents.toInt() < maxStudents) {
            xlsx.write(row, rowNavigator.studentQuantiti, maxStudents);
        }
    }

    qDebug() << "Saving to:" << outputPath;

    if (!xlsx.saveAs(outputPath)) {
        QString tempPath = outputPath + ".temp";
        if (xlsx.saveAs(tempPath)) {
            if (!QFile::rename(tempPath, outputPath)) {
                qDebug() << "Failed to rename temp file";
                throw std::runtime_error("FAILED_RENAME_EXPORT");
            }
        } else {
            qDebug() << "Both saveAs attempts failed";
            throw std::runtime_error("FAILED_SAVE_EXPORT");
        }
    }

    if (QFile::exists(outputPath)) {
        qDebug() << "File created successfully, size:" << QFileInfo(outputPath).size();
    } else {
        qDebug() << "File was not created!";
        throw std::runtime_error("FILE_NOT_CREATED");
    }
}