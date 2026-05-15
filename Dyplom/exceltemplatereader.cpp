#include "ExcelTemplateReader.h"
#include "xlsxdocument.h"
#include <stdexcept>
#include <QStringList>
#include <QRegularExpression>

using namespace QXlsx;

ImportWorkbookDto ExcelTemplateReader::read(const QString& filePath){
    Document doc(filePath);

    if (doc.sheetNames().isEmpty()) {
        throw std::runtime_error("Excel file is empty or unreadable");
    }

    ImportWorkbookDto workbook;

    for (const auto& sheetName : doc.sheetNames()) {
        doc.selectSheet(sheetName);
        workbook.sheets.append(readSheet(doc, sheetName));
    }

    return workbook;
}

ImportSheetDto ExcelTemplateReader::readSheet(Document& doc, const QString& sheetName){
    ImportSheetDto sheet;
    sheet.sheetName = sheetName;
    sheet.header = readHeader(doc);
    sheet.rows = readRows(doc);
    return sheet;
}

GroupHeaderDto ExcelTemplateReader::readHeader(Document& doc){
    GroupHeaderDto header;

    const QString row1 = doc.read("A1").toString().trimmed();
    const QString row2 = doc.read("A2").toString().trimmed();
    const QString row3 = doc.read("A3").toString().trimmed();

    // A1
    // specialityNumber = second world
    {
        const QStringList parts = row1.split(' ', Qt::SkipEmptyParts);
        if (parts.size() >= 2)
            header.specialityNumber = parts[1].toInt();
    }

    // A2
    // groupName    = the second word before "-"
    // groupYear    = the second word after "-" + 2000
    {
        QRegularExpression re(R"(^\S+\s+([A-ZА-ЯІЇЄҐa-zа-яіїєґ]+)-(\d{2}))");
        auto match = re.match(row2);

        if (match.hasMatch()) {
            header.groupName = match.captured(1).trimmed();
            header.groupYear = 2000 + match.captured(2).toInt();
        }
    }

    // A3
    // groupCount   = 3rd word
    // studentCount = 6rd word
    {
        const QStringList parts = row3.split(' ', Qt::SkipEmptyParts);

        if (parts.size() >= 3)
            header.groupCount = parts[2].toInt();

        if (parts.size() >= 6)
            header.studentCount = parts[5].toInt();
    }

    return header;
}

QList<DisciplineRowDto> ExcelTemplateReader::readRows(Document& doc){
    QList<DisciplineRowDto> rows;

    constexpr int startRow = 10;

    const int sem1Weeks = doc.read("O7").toString().split(' ', Qt::SkipEmptyParts).value(0).toInt();
    const int sem2Weeks = doc.read("S7").toString().split(' ', Qt::SkipEmptyParts).value(0).toInt();

    auto getFirstWordInt = [](const QVariant& v) -> int {
        QString text = v.toString().trimmed();

        if (text.isEmpty())
            return 0;

        QString firstWord = text.split(' ', Qt::SkipEmptyParts).value(0);

        return firstWord.toInt();
    };

    for (int row = startRow;; ++row) {
        const QString disciplineName = doc.read(row, 2).toString().trimmed(); // B
        if (disciplineName.isEmpty())
            break;

        const QString departmentName = doc.read(row, 3).toString().trimmed(); // C

        const QVariant exams         = doc.read(row, 7);  // G
        //const QVariant courseProject = doc.read(row, 9);  // I

        // semester 1
        const QVariant sem1Lectures = doc.read(row, 15); // O
        const QVariant sem1Practice = doc.read(row, 16); // P
        const QVariant sem1Labs     = doc.read(row, 17); // Q

        // semester 2
        const QVariant sem2Lectures = doc.read(row, 19); // S
        const QVariant sem2Practice = doc.read(row, 20); // T
        const QVariant sem2Labs     = doc.read(row, 21); // U

        auto hasSemesterLoad = [](const QVariant& l, const QVariant& p, const QVariant& lab) {
            return l.toInt() > 0 || p.toInt() > 0 || lab.toInt() > 0;
        };

        const int examSemester = (exams.toInt() % 2 == 0) ? 2 : 1;
        // semester 1
        if (hasSemesterLoad(sem1Lectures, sem1Practice, sem1Labs) || examSemester == 1 /*|| courseProject.toInt() > 0*/) {
            DisciplineRowDto item;
            item.excelRow = row;
            item.disciplineName = disciplineName;
            item.departmentName = departmentName;

            item.lectures = sem1Lectures;
            item.practice = sem1Practice;
            item.labs = sem1Labs;
            item.exams = (examSemester == 1) ? exams : QVariant();
            //item.courseProject = courseProject;

            item.semester = getFirstWordInt(doc.read(6, 15));
            item.weeks = sem1Weeks;

            rows.append(item);
        }

        // semester 2
        if (hasSemesterLoad(sem2Lectures, sem2Practice, sem2Labs) || examSemester == 2) {
            DisciplineRowDto item;
            item.excelRow = row;
            item.disciplineName = disciplineName;
            item.departmentName = departmentName;

            item.lectures = sem2Lectures;
            item.practice = sem2Practice;
            item.labs = sem2Labs;
            item.exams = (examSemester == 2) ? exams : QVariant();

            item.semester = getFirstWordInt(doc.read(6, 19));
            item.weeks = sem2Weeks;

            rows.append(item);
        }
    }

    return rows;
}