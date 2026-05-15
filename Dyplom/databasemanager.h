#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include "datamodels.h"

#define PATH_CONFIG_FILE "/db_config.json"
#define SQL_PATH(file) QString(":/sqlRequest/sql/") + file

#define LECTION_ID 1
#define ASSISTANT_ID 1

class DatabaseManager
{
public:
    static DatabaseManager& instance() {
        static DatabaseManager _instance;
        return _instance;
    }

private:
    struct PIB{
        QString fName;
        QString sName;
        QString lName;
    };

    DatabaseManager();
    ~DatabaseManager();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    void DbConnect();

    QSqlDatabase db;
    QStringList expandPIB(QString PIB);

    void tryExec(QSqlQuery& query, const QString& context);
    QVariantMap readDbConfig();
    QString loadSql(const QString& path);
    void insertTeacher(QString PIB, int postID, QSqlQuery& query);
    void insertLoad(int rate, int teacherID, int year, QSqlQuery& query, int otherLoad);
    QVariant nullInt(float v);

public:
    QSqlQuery getTeacherData(int yearConfig);
    QSqlQuery getEnumConfig();
    QSqlQuery getYearConfig(int yearConfig);
    QSqlQuery getLoadData(int yearConfig);
    QSqlQuery getGroupData(int yearConfig);
    QSqlQuery getSpecialityData();
    QSqlQuery getAllPost();
    QSqlQuery getTeacherDataByID(int teacherID, int yearConfig);
    QSqlQuery getAllDiscipline();
    QSqlQuery getAllDisciplineType();
    QSqlQuery getAllGroup();
    QSqlQuery getAllTeacherPIB();
    QSqlQuery getDisciplineActivityByID(int disciplineActivityID);
    QSqlQuery getSpecialityName();
    QSqlQuery getGroupByID(int studentGroupID, int configYear);
    QSqlQuery getAllDepartment();
    QSqlQuery getSpecialityByID(int specialityNumber);
    int       getDepartmentIdByName(QString departmentName);
    QSqlQuery getExportTeacherLoad(int teacherId, int yearConfig);
    QPair<QString, double> getTeacherHeaderInfo(int teacherId, int yearConfig);
    int       getPostId(int teacherId);
    int       getActivityId(int disciplyneId);

    void updateTeacher(TeacherData teacher);
    void updatePost(int postID, QString postName);
    void updateDiscipline(int disciplineID, QString disciplineName);
    void updateDisciplineType(int disciplineTypeID, QString disciplineTypeName);
    void updateDisciplineActivity(DisciplineActivityData activity);
    void updateDepartment(int departmentID, QString departmentName);
    void updateGroup(GroupData group);
    void updateSpeciality(int specialityNumber, int departmentID, QString specialityName);
    void updateYearConfig(YearConfigData config);

    void addTeacher(TeacherData teacher);
    void addPost(QString postName);
    int  addDiscipline(QString disciplineName);
    void addDisciplineType(QString disciplineTypeName);
    void addDisciplineActivity(DisciplineActivityData activity);
    void addGroup(GroupData group);
    int  addDepartment(QString departmentName);
    void addSpeciality(int specialityNumber, int departmentID, QString specialityName);
    void addYearConfig(YearConfigData config);

    void deleteTeacher(int teacherID);
    void deletePost(int postID);
    void deleteDiscipline(int disciplineID);
    void deleteDisciplineType(int disciplineTypeID);
    void deleteDisciplineActivity(int disciplineActivityID); //since disciplineActivityID in the DB has a modifier UNIQUE we can only use it to explicitly identify the record
    void deleteGroup(int studentGroupID);
    void deleteDepartment(int departmentID);
    void deleteSpeciality(int specialityNumber);

    int  getOrCreateDepartment(QString departmentName);
    void getOrCreateSpeciality(QString specialytiName, int specialituNumber, int departmentID);
    int* getOrCreateGroup(int specialityNumber, int groupYear, int groupCount, int year, int studentQuantiti);
    int  getOrCreateDiscipline(QString disciplineName);

    bool isGroupActivity(int activityId);

    void reconnect();
};

#endif // DATABASEMANAGER_H
