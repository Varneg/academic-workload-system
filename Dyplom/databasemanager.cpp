#include "databasemanager.h"
#include <QDebug>
#include <QCoreApplication>
#include <QtSql/QSql>
#include <QMessageBox>
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QVariant>

DatabaseManager::DatabaseManager() {
    if (QSqlDatabase::contains()) {
        db = QSqlDatabase::database();
    } else {
        db = QSqlDatabase::addDatabase("QMYSQL");
    }

    DbConnect();
}

QVariantMap DatabaseManager::readDbConfig() {
    QString filePath = QCoreApplication::applicationDirPath() + PATH_CONFIG_FILE;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error(("Не вдалося відкрити файл конфігурацій: " + filePath.toStdString()));
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) {
        throw std::runtime_error("Некорректний JSON файл конфігурацій");
    }

    QJsonObject obj = doc.object();
    QVariantMap config;

    config["host"] = obj.value("host").toString();
    config["port"] = obj.value("port").toInt();
    config["database"] = obj.value("database").toString();
    config["username"] = obj.value("username").toString();
    config["password"] = obj.value("password").toString();

    return config;
}

DatabaseManager::~DatabaseManager() {
    if (db.isOpen()) db.close();
}

void DatabaseManager::DbConnect(){
/*
    qDebug() << "QT_PLUGIN_PATH:" << qgetenv("QT_PLUGIN_PATH");
    qDebug() << "Application Dir:" << QCoreApplication::applicationDirPath();

    qDebug() << "DB ERROR:" << db.lastError().text();
*/
    QVariantMap config = readDbConfig();

    db.setHostName(config.value("host").toString());
    db.setPort(config.value("port").toInt());
    db.setDatabaseName(config.value("database").toString());
    db.setUserName(config.value("username").toString());
    db.setPassword(config.value("password").toString());

    if(!db.open()){
        throw std::runtime_error("Не вдалося під’єднатися до бази даних");
    }
}

void DatabaseManager::reconnect(){
    if (db.isOpen())
        db.close();

    DbConnect();
}

void DatabaseManager::tryExec(QSqlQuery& query, const QString& context){
    if(!query.exec()){
        QString errorText = query.lastError().text();

        bool connectionLost =
            errorText.contains("server has gone away", Qt::CaseInsensitive) ||
            errorText.contains("lost connection", Qt::CaseInsensitive);


        if (connectionLost) {
            throw std::runtime_error("DB_CONNECTION_LOST");
        }

        QString error = QString("SQL Error [%1]: %2\nQuery: %3")
                            .arg(context)
                            .arg(errorText)
                            .arg(query.lastQuery());

        throw std::runtime_error(error.toStdString());
    }
}

QString DatabaseManager::loadSql(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("Не вдалося відкрити файл з запитами: " + path.toStdString());

    return QString::fromUtf8(file.readAll());
}

QVariant DatabaseManager::nullInt(float v){
    return v < 0 ? QVariant(QMetaType::fromType<float>()) : QVariant(v);
}

QSqlQuery DatabaseManager::getTeacherData(int yearConfig){
    QSqlQuery query;
    QString sql = loadSql(SQL_PATH("get_teacher_data.sql"));
    query.prepare(sql);
    query.bindValue(":yearConfig", yearConfig);

    tryExec(query, "getTeacherData");

    return query;
}

QSqlQuery DatabaseManager::getEnumConfig(){
    QSqlQuery query;
    query.prepare("SELECT ConfigYear FROM config");
    tryExec(query, "getEnumConfig");

    return query;
}

QSqlQuery DatabaseManager::getYearConfig(int yearConfig){
    QSqlQuery query;
    query.prepare("SELECT * FROM config WHERE ConfigYear = :yearConfig");
    query.bindValue(":yearConfig", yearConfig);
    tryExec(query, "getYearConfig");

    return query;
}

QSqlQuery DatabaseManager::getLoadData(int yearConfig){
    QSqlQuery query;

    QString sql = loadSql(SQL_PATH("get_load_data.sql"));
    query.prepare(sql);

    query.bindValue(":yearConfig", yearConfig);
    tryExec(query, "getLoadData");

    return query;
}

QSqlQuery DatabaseManager::getGroupData(int yearConfig){
    QSqlQuery query;

    QString sql = loadSql(SQL_PATH("get_group_data.sql"));
    query.prepare(sql);

    query.bindValue(":yearConfig", yearConfig);
    tryExec(query, "getGroupData");

    return query;
}

QSqlQuery DatabaseManager::getSpecialityData(){
    QSqlQuery query;

    QString sql = loadSql(SQL_PATH("get_speciality_data.sql"));
    query.prepare(sql);

    tryExec(query, "getSpecialityData");

    return query;
}

QStringList DatabaseManager::expandPIB(QString PIB){
    QStringList parts = PIB.split(' ', Qt::SkipEmptyParts);

    if (parts.size() < 2)
        throw std::runtime_error("Invalid PIB format");

    return parts;
}

void DatabaseManager::insertTeacher(QString PIB, int postID, QSqlQuery& query){
    QStringList exPIB = expandPIB(PIB);

    query.prepare("INSERT INTO Teacher (FName, SName, LName, PostID) VALUES (:fName, :sName, :lName, :postID);");
    query.bindValue(":fName", exPIB[1]);
    query.bindValue(":sName", exPIB[0]);
    query.bindValue(":lName", (exPIB.length() > 2) ? exPIB[2] : "");
    query.bindValue(":postID", postID);

    tryExec(query, "insertTeacher");
}

void DatabaseManager::insertLoad(int rate, int teacherID, int year, QSqlQuery& query, int otherLoad){
    query.prepare("INSERT INTO LoadaOnYear (TeacherID, AcademicYear, TimeOtherLoad, Rate) VALUES (:teacherID, :year, :otherLoad, :rate);");
    query.bindValue(":teacherID", teacherID);
    query.bindValue(":year", year);
    query.bindValue(":rate", rate);
    query.bindValue(":otherLoad", otherLoad);

    tryExec(query, "insertLoad");
}

void DatabaseManager::addTeacher(TeacherData teacher){
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        throw std::runtime_error("Не вдалося почати транзакцію");
    }

    try {
        QSqlQuery query;

        insertTeacher(teacher.PIB, teacher.postID, query);
        int teacherID = query.lastInsertId().toInt();

        query.prepare("SELECT MAX(ConfigYear) AS year FROM Config");
        tryExec(query, "get_latest_year");

        if (!query.next())
            throw std::runtime_error("Config is empty");

        int year = query.value(0).toInt();

        insertLoad(teacher.rate, teacherID, year, query, teacher.otherLoad);

        db.commit();
    }
    catch (...) {
        db.rollback();
        throw;
    }
}

QSqlQuery DatabaseManager::getAllPost(){
    QSqlQuery query;
    query.prepare("SELECT * FROM post");
    tryExec(query, "getAllPost");

    return query;
}

QSqlQuery DatabaseManager::getTeacherDataByID(int teacherID, int yearConfig){
    QSqlQuery query;

    QString sql = loadSql(SQL_PATH("get_teacher_data_by_id.sql"));
    query.prepare(sql);
    query.bindValue(":teacherID", teacherID);
    query.bindValue(":yearConfig", yearConfig);

    tryExec(query, "getTeacherDataByID");

    return query;
}

void DatabaseManager::updateTeacher(TeacherData teacher){
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        throw std::runtime_error("Не вдалося почати транзакцію");
    }

    QStringList exPIB = expandPIB(teacher.PIB);

    try {
        QSqlQuery query;

        query.prepare("UPDATE teacher SET FName = :fName, SName = :sName, LName = :lName, PostID = :postID WHERE TecherID = :teacherID");
        query.bindValue(":fName", exPIB[1]);
        query.bindValue(":sName", exPIB[0]);
        query.bindValue(":lName", (exPIB.length() > 2) ? exPIB[2] : "");
        query.bindValue(":postID", teacher.postID);
        query.bindValue(":teacherID", teacher.teacherID);
        tryExec(query, "updateTeacher_teacher");

        query.prepare("UPDATE loadaonyear SET Rate = :rate, TimeOtherLoad = :otherLoad WHERE TeacherID = :teacherID AND AcademicYear = :configYear");
        query.bindValue(":rate", teacher.rate);
        query.bindValue(":teacherID", teacher.teacherID);
        query.bindValue(":configYear", teacher.configYear);
        query.bindValue(":otherLoad", teacher.otherLoad);
        tryExec(query, "updateTeacher_loadaonyear");

        db.commit();
    } catch (...) {
        db.rollback();
        qDebug() << "Transaction failed";
        throw;
    }
}

void DatabaseManager::deleteTeacher(int teacherID)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        throw std::runtime_error("Не вдалося почати транзакцію");
    }

    try {
        QSqlQuery query;

        //Check TeachingLoad
        query.prepare(R"(
            SELECT COUNT(*)
            FROM TeachingLoad
            WHERE TecherID = :id
        )");
        query.bindValue(":id", teacherID);
        tryExec(query, "CheckTeachingLoad");

        query.next();
        if (query.value(0).toInt() > 0) {
            db.rollback();
            throw std::runtime_error("Неможливо видалити викладача: є навчальне навантаження");
        }

        // Delete LoadaOnYear (if there is)
        query.prepare(R"(
            DELETE FROM LoadaOnYear
            WHERE TeacherID = :id
        )");
        query.bindValue(":id", teacherID);
        tryExec(query, "DeleteLoadaOnYear");

        // Delete teacher
        query.prepare(R"(
            DELETE FROM Teacher
            WHERE TecherID = :id
        )");
        query.bindValue(":id", teacherID);
        tryExec(query, "DeleteTeacher");

        db.commit();
    }
    catch (const std::exception &e) {
        db.rollback();
        throw;
    }
}

void DatabaseManager::addPost(QString postName){
    QSqlQuery query;

    query.prepare(R"(
        INSERT INTO post(PostName) VALUE
        (:postName);
    )");
    query.bindValue(":postName", postName);

    tryExec(query, "addPost");
}

void DatabaseManager::updatePost(int postID, QString postName){
    QSqlQuery query;

    query.prepare(R"(
        UPDATE post
        SET PostName = :postName
        WHERE PostID = :postID
    )");

    query.bindValue(":postID", postID);
    query.bindValue(":postName", postName);

    tryExec(query, "updatePost");
}

void DatabaseManager::deletePost(int postID){
    QSqlQuery query;

    query.prepare(R"(
        SELECT COUNT(*)
        FROM teacher
        WHERE PostID = :postID
    )");
    query.bindValue(":postID", postID);


    tryExec(query, "checkPostUsage");
    if(query.next() && query.value(0).toInt() > 0){
        throw std::runtime_error("Неможливо видалити посаду: існують викладачі з цією посадою");
    }

    query.prepare(R"(
        DELETE FROM post
        WHERE PostID = :postID
    )");
    query.bindValue(":postID", postID);

    tryExec(query, "deletePost");
}

QSqlQuery DatabaseManager::getAllDiscipline(){
    QSqlQuery query;

    query.prepare(R"(
        SELECT *
        FROM discipline
    )");
    tryExec(query, "getAllDiscipline");

    return query;
}

QSqlQuery DatabaseManager::getAllDisciplineType(){
    QSqlQuery query;

    query.prepare(R"(
        SELECT ActivityID, ActivityName
        FROM TypeActivity
    )");
    tryExec(query, "getAllDisciplineType");

    return query;
}

void DatabaseManager::updateDiscipline(int disciplineID, QString disciplineName){
    QSqlQuery query;

    query.prepare(R"(
        UPDATE discipline
        SET DisciplineName = :disciplineName
        WHERE DisciplineID = :disciplineID
    )");

    query.bindValue(":disciplineID", disciplineID);
    query.bindValue(":disciplineName", disciplineName);

    tryExec(query, "updateDiscipline");
}

int DatabaseManager::addDiscipline(QString disciplineName){
    QSqlQuery query;

    query.prepare(R"(
        INSERT INTO discipline(DisciplineName) VALUE
        (:disciplineName);
    )");
    query.bindValue(":disciplineName", disciplineName);

    tryExec(query, "addDiscipline");

    return query.lastInsertId().toInt();
}

void DatabaseManager::deleteDiscipline(int disciplineID){
    QSqlQuery query;

    query.prepare(R"(
        SELECT COUNT(*)
        FROM disciplineactivity
        WHERE DisciplineID = :disciplineID
    )");
    query.bindValue(":disciplineID", disciplineID);


    tryExec(query, "checkDisciplineActivityUsage");
    if(query.next() && query.value(0).toInt() > 0){
        throw std::runtime_error("Неможливо видалити дисципліну: існує запланована дисипліна");
    }

    query.prepare(R"(
        DELETE FROM discipline
        WHERE DisciplineID = :disciplineID
    )");
    query.bindValue(":disciplineID", disciplineID);

    tryExec(query, "deleteDiscipline");
}

void DatabaseManager::updateDisciplineType(int disciplineTypeID, QString disciplineTypeName){
    QSqlQuery query;

    query.prepare(R"(
        UPDATE typeactivity
        SET ActivityName = :disciplineName
        WHERE ActivityID = :disciplineID
    )");

    query.bindValue(":disciplineID", disciplineTypeID);
    query.bindValue(":disciplineName", disciplineTypeName);

    tryExec(query, "updateDisciplineType");
}

void DatabaseManager::addDisciplineType(QString disciplineTypeName){
    QSqlQuery query;

    query.prepare(R"(
        INSERT INTO typeactivity(ActivityName) VALUE
        (:disciplineTypeName);
    )");
    query.bindValue(":disciplineTypeName", disciplineTypeName);

    tryExec(query, "addDisciplineType");
}

void DatabaseManager::deleteDisciplineType(int disciplineTypeID){
    QSqlQuery query;

    query.prepare(R"(
        SELECT COUNT(*)
        FROM disciplineactivity
        WHERE ActivityID = :disciplineTypeID
    )");
    query.bindValue(":disciplineTypeID", disciplineTypeID);


    tryExec(query, "checkDisciplineActivityUsage");
    if(query.next() && query.value(0).toInt() > 0){
        throw std::runtime_error("Неможливо видалити тип дисципліни: існує запланована дисипліна з даним типом");
    }

    query.prepare(R"(
        DELETE FROM typeactivity
        WHERE ActivityID = :disciplineTypeID
    )");
    query.bindValue(":disciplineTypeID", disciplineTypeID);

    tryExec(query, "deleteDisciplineType");
}

QSqlQuery DatabaseManager::getAllGroup(){
    QSqlQuery query;

    query.prepare(R"(
        SELECT
            StudentGroupID,
            CONCAT(s.SpecialityName, '-', RIGHT(GroupYear, 2), '-', sg.GroupNumber) AS `Group`

        FROM StudentGroup sg
        JOIN speciality s
            ON sg.SpecialityNumber = s.SpecialityNumber
    )");

    tryExec(query, "getAllGroup");

    return query;
}

QSqlQuery DatabaseManager::getAllTeacherPIB(){
    QSqlQuery query;

    query.prepare(R"(
        SELECT
            TecherID,
            CONCAT(SName, ' ', FName, ' ', IFNULL(LName, '')) AS PIB
        FROM
            teacher
    )");

    tryExec(query, "getAllTeacherPIB");

    return query;
}

void DatabaseManager::addDisciplineActivity(DisciplineActivityData activity){
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        throw std::runtime_error("Не вдалося почати транзакцію");
    }

    try {
        QSqlQuery query;

        if(getPostId(activity.teacherID) == ASSISTANT_ID && activity.disciplineTypeID == LECTION_ID){
            throw std::runtime_error("Асистенту не можна назначати лекції");
        }

        if(activity.disciplineTypeID == 5){ // 5 - cursWork
            activity.totalHour = activity.quantityStudent * 2;
        }

        query.prepare(R"(
            INSERT INTO disciplineactivity(ActivityID, DisciplineID, StudentGroupID, TimePerWeek, GeneralTime, DisciplineYear, Semester, QuantityStudent) value
            (:disciplineTypeID, :disciplineID, :groupID, :hourPerWeak, :totalHour, :curentYear, :semestr, :quantityStudent);
        )");

        query.bindValue(":disciplineTypeID", nullInt(activity.disciplineTypeID));
        query.bindValue(":disciplineID", nullInt(activity.disciplineID));
        query.bindValue(":groupID", nullInt(activity.groupID));
        query.bindValue(":hourPerWeak", nullInt(activity.hourPerWeek));
        query.bindValue(":totalHour", nullInt(activity.totalHour));
        query.bindValue(":curentYear", nullInt(activity.currentYear));
        query.bindValue(":semestr", nullInt(activity.semestr));
        query.bindValue(":quantityStudent", nullInt(activity.quantityStudent));

        tryExec(query, "addDisciplineActivity");

        int disciplineActivityID = query.lastInsertId().toInt();

        if(nullInt(activity.teacherID).toBool()){
            query.prepare(R"(
                INSERT INTO teachingload(DisciplineActivityID, TecherID) value
                (:disciplineActivityID, :teacherID);
            )");

            query.bindValue(":disciplineActivityID", disciplineActivityID);
            query.bindValue(":teacherID", activity.teacherID);

            tryExec(query, "addDisciplineActivity");
        }

        query.prepare(R"(
            INSERT IGNORE INTO LoadaOnYear (TeacherID, AcademicYear)
            VALUES (:teacherID, :year);
        )");
        query.bindValue(":teacherID", activity.teacherID);
        query.bindValue(":year", activity.currentYear);
        tryExec(query, "addDisciplineActivity");

        db.commit();
    }
    catch (const std::exception& e) {
        db.rollback();
        throw;
    }
}

void DatabaseManager::deleteDisciplineActivity(int disciplineActivityID){
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        throw std::runtime_error("Не вдалося почати транзакцію");
    }

    try {
        QSqlQuery query;

        query.prepare("DELETE FROM teachingload WHERE DisciplineActivityID = :disciplineActivityID");
        query.bindValue(":disciplineActivityID", disciplineActivityID);
        tryExec(query, "Delete teachingload");

        query.prepare("DELETE FROM disciplineactivity WHERE DisciplineActivity = :disciplineActivityID");
        query.bindValue(":disciplineActivityID", disciplineActivityID);
        tryExec(query, "deleteDisciplineActivity");
        //qDebug() << "delete DisciplineActivity with id: " << disciplineActivityID;

        db.commit();
    } catch (const std::exception& e) {
        db.rollback();
        throw;
    }
}

QSqlQuery DatabaseManager::getDisciplineActivityByID(int disciplineActivity){
    QSqlQuery query;

    query.prepare(R"(
        SELECT
            da.DisciplineID,
            da.ActivityID,
            da.StudentGroupID,
            tl.TecherID,
            da.GeneralTime,
            da.TimePerWeek,
            da.Semester,
            da.QuantityStudent
        FROM
            disciplineactivity da
        LEFT JOIN
            teachingload tl
            ON da.DisciplineActivity = tl.DisciplineActivityID
        WHERE
            da.DisciplineActivity = :disciplineActivity
    )");
    query.bindValue(":disciplineActivity", disciplineActivity);
    tryExec(query, "getDisciplineActivityByID");

    return query;
}

void DatabaseManager::updateDisciplineActivity(DisciplineActivityData activity){
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        throw std::runtime_error("Не вдалося почати транзакцію");
    }

    if(getPostId(activity.teacherID) == ASSISTANT_ID && activity.disciplineTypeID == LECTION_ID){
        throw std::runtime_error("Асистенту не можна назначати лекції");
    }

    if(activity.disciplineTypeID == 5){ // 5 - cursWork
        activity.totalHour = activity.quantityStudent * 2;
    }

    try {
        QSqlQuery query;

        query.prepare(R"(
        UPDATE disciplineactivity
        SET
            ActivityID = :disciplineTypeID,
            DisciplineID = :disciplineID,
            StudentGroupID = :groupID,
            TimePerWeek = :hourPerWeak,
            GeneralTime = :totalHour,
            DisciplineYear = :curentYear,
            Semester = :semestr,
            QuantityStudent = :quantityStudent
        WHERE DisciplineActivity = :disciplineActivityID;
    )");

        query.bindValue(":disciplineTypeID", nullInt(activity.disciplineTypeID));
        query.bindValue(":disciplineID", nullInt(activity.disciplineID));
        query.bindValue(":groupID", nullInt(activity.groupID));
        query.bindValue(":hourPerWeak", nullInt(activity.hourPerWeek));
        query.bindValue(":totalHour", nullInt(activity.totalHour));
        query.bindValue(":curentYear", nullInt(activity.currentYear));
        query.bindValue(":semestr", nullInt(activity.semestr));
        query.bindValue(":quantityStudent", nullInt(activity.quantityStudent));
        query.bindValue(":disciplineActivityID", activity.disciplineActivityID);

        tryExec(query, "updateDisciplineActivity");

        if (activity.teacherID >= 0) {
            query.prepare(R"(
            UPDATE teachingload
            SET TecherID = :teacherID
            WHERE DisciplineActivityID = :disciplineActivityID;
        )");

            query.bindValue(":teacherID", activity.teacherID);
            query.bindValue(":disciplineActivityID", activity.disciplineActivityID);

            tryExec(query, "updateTeachingLoad");

            if (query.numRowsAffected() == 0) {
                query.prepare(R"(
                    INSERT INTO teachingload (DisciplineActivityID, TecherID)
                    VALUES (:disciplineActivityID, :teacherID)
                    ON DUPLICATE KEY UPDATE
                        TecherID = VALUES(TecherID);
                )");

                query.bindValue(":disciplineActivityID", activity.disciplineActivityID);
                query.bindValue(":teacherID", activity.teacherID);

                tryExec(query, "insertTeachingLoad");
            }
        } else {
            query.prepare(R"(
            DELETE FROM teachingload
            WHERE DisciplineActivityID = :disciplineActivityID;
        )");

            query.bindValue(":disciplineActivityID", activity.disciplineActivityID);
            tryExec(query, "deleteTeachingLoad");
        }

        db.commit();
    }
    catch (const std::exception&) {
        db.rollback();
        throw;
    }
}

QSqlQuery DatabaseManager::getSpecialityName(){
    QSqlQuery query;

    query.prepare("SELECT SpecialityNumber, SpecialityName FROM speciality");
    tryExec(query, "getSpecialityName");

    return query;
}

void DatabaseManager::addGroup(GroupData group){
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        throw std::runtime_error("Не вдалося почати транзакцію");
    }

    try {
        QSqlQuery query;
        query.prepare(R"(
            INSERT INTO studentgroup(SpecialityNumber, GroupYear, GroupNumber) VALUES
            (:specialytiNumber, :year, :subgroup);
        )");
        query.bindValue(":specialytiNumber", nullInt(group.specialityNumber));
        query.bindValue(":year", nullInt(group.groupYear));
        query.bindValue(":subgroup", nullInt(group.subgroup));
        tryExec(query, "studentgroup");

        int studentGroupID = query.lastInsertId().toInt();

        query.prepare(R"(
            INSERT INTO quantitystudentongroup(StudentGroupID, SettingsYear, QuantityStudent) VALUES
            (:studentGroupID, :configYear, :quantityStudent);
        )");
        query.bindValue(":studentGroupID", nullInt(studentGroupID));
        query.bindValue(":configYear", nullInt(group.configYear));
        query.bindValue(":quantityStudent", nullInt(group.quantityStudent));
        tryExec(query, "quantitystudentongroup");

        db.commit();
    }catch (const std::exception&) {
        db.rollback();
        throw;
    }
}

void DatabaseManager::updateGroup(GroupData group){
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        throw std::runtime_error("Не вдалося почати транзакцію");
    }

    try {
        QSqlQuery query;
        query.prepare(R"(
            UPDATE studentgroup
            SET SpecialityNumber = :specialytiNumber,
                GroupYear = :year,
                GroupNumber = :subgroup
            WHERE StudentGroupID = :studentGroupID;
        )");

        query.bindValue(":specialytiNumber", nullInt(group.specialityNumber));
        query.bindValue(":year", nullInt(group.groupYear));
        query.bindValue(":subgroup", nullInt(group.subgroup));
        query.bindValue(":studentGroupID", nullInt(group.studentGroupID));
        tryExec(query, "studentgroup");

        query.prepare(R"(
            UPDATE quantitystudentongroup
            SET QuantityStudent = :quantityStudent
            WHERE StudentGroupID = :studentGroupID
              AND SettingsYear = :configYear;
        )");

        query.bindValue(":quantityStudent", nullInt(group.quantityStudent));
        query.bindValue(":studentGroupID", nullInt(group.studentGroupID));
        query.bindValue(":configYear", nullInt(group.configYear));
        tryExec(query, "quantitystudentongroup");

        db.commit();
    }
    catch (const std::exception&) {
        db.rollback();
        throw;
    }
}

QSqlQuery DatabaseManager::getGroupByID(int studentGroupID, int configYear){
    QSqlQuery query;

    query.prepare(R"(
        SELECT
            sg.SpecialityNumber,
            sg.GroupYear AS Year,
            sg.GroupNumber,
            qsg.QuantityStudent

        FROM
            studentgroup sg

        LEFT JOIN
            quantitystudentongroup qsg
                    ON sg.StudentGroupID = qsg.StudentGroupID

        WHERE
            qsg.SettingsYear = :configYear AND sg.StudentGroupID = :studentGroupID;
    )");
    query.bindValue(":configYear", configYear);
    query.bindValue(":studentGroupID", studentGroupID);
    tryExec(query, "getGroupByID");

    return query;
}

void DatabaseManager::deleteGroup(int studentGroupID){
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        throw std::runtime_error("Не вдалося почати транзакцію");
    }

    try {
        QSqlQuery query;

        query.prepare(R"(
            SELECT COUNT(*)
            FROM disciplineactivity
            WHERE StudentGroupID = :studentGroupID;
        )");
        query.bindValue(":studentGroupID", studentGroupID);

        tryExec(query, "disciplineactivity check");

        if (query.next() && query.value(0).toInt() > 0) {
            throw std::runtime_error("Неможливо видалити групу: є пов'язані записи в disciplineactivity");
        }

        query.prepare(R"(
            DELETE FROM quantitystudentongroup
            WHERE StudentGroupID = :studentGroupID;
        )");
        query.bindValue(":studentGroupID", studentGroupID);
        tryExec(query, "quantitystudentongroup");

        query.prepare(R"(
            DELETE FROM studentgroup
            WHERE StudentGroupID = :studentGroupID;
        )");
        query.bindValue(":studentGroupID", studentGroupID);
        tryExec(query, "studentgroup");

        db.commit();
    }
    catch (const std::exception&) {
        db.rollback();
        throw;
    }
}

QSqlQuery DatabaseManager::getAllDepartment(){
    QSqlQuery query;

    query.prepare("SELECT * FROM department");
    tryExec(query, "getAllDepartment");

    return query;
}

void DatabaseManager::updateDepartment(int departmentID, QString departmentName){
    QSqlQuery query;

    query.prepare(R"(
        UPDATE Department
        SET DepartmentName = :departmentName
        WHERE DepartmentID = :departmentID;
    )");

    query.bindValue(":departmentName", departmentName);
    query.bindValue(":departmentID", departmentID);

    tryExec(query, "updateDepartment");
}

int DatabaseManager::addDepartment(QString departmentName){
    QSqlQuery query;

    query.prepare(R"(
        INSERT INTO Department (DepartmentName)
        VALUES (:departmentName);
    )");

    query.bindValue(":departmentName", departmentName);

    tryExec(query, "addDepartment");

    return query.lastInsertId().toInt();
}

void DatabaseManager::deleteDepartment(int departmentID){
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        throw std::runtime_error("Не вдалося почати транзакцію");
    }

    try {
        QSqlQuery query;

        query.prepare(R"(
            SELECT COUNT(*)
            FROM speciality
            WHERE DepartmentID = :departmentID;
        )");

        query.bindValue(":departmentID", departmentID);
        tryExec(query, "checkDepartmentUsage");

        if (query.next() && query.value(0).toInt() > 0) {
            throw std::runtime_error("Неможливо видалити кафедру: є пов'язані записи");
        }

        query.prepare(R"(
            DELETE FROM Department
            WHERE DepartmentID = :departmentID;
        )");

        query.bindValue(":departmentID", departmentID);
        tryExec(query, "deleteDepartment");

        db.commit();
    }
    catch (const std::exception&) {
        db.rollback();
        throw;
    }
}

void DatabaseManager::addSpeciality(int specialityNumber, int departmentID, QString specialityName){
    QSqlQuery query;

    query.prepare(R"(
        INSERT INTO speciality(SpecialityNumber, DepartmentID, SpecialityName) VALUES
        (:specialityNumber, :departmentID, :specialityName);
    )");
    query.bindValue(":specialityNumber", specialityNumber);
    query.bindValue(":departmentID", departmentID);
    query.bindValue(":specialityName", specialityName);
    tryExec(query, "addSpeciality");
}

void DatabaseManager::updateSpeciality(int specialityNumber, int departmentID, QString specialityName){
    QSqlQuery query;

    query.prepare(R"(
        UPDATE speciality
        SET DepartmentID = :departmentID,
            SpecialityName = :specialityName
        WHERE SpecialityNumber = :specialityNumber;
    )");

    query.bindValue(":specialityNumber", specialityNumber);
    query.bindValue(":departmentID", departmentID);
    query.bindValue(":specialityName", specialityName);

    tryExec(query, "updateSpeciality");
}

void DatabaseManager::deleteSpeciality(int specialityNumber){
    QSqlQuery query;

    query.prepare(R"(
        SELECT COUNT(*)
        FROM StudentGroup
        WHERE SpecialityNumber = :specialityNumber;
    )");
    query.bindValue(":specialityNumber", specialityNumber);

    tryExec(query, "deleteSpeciality_check");

    if (query.next() && query.value(0).toInt() > 0) {
        throw std::runtime_error("Неможливо видалити спеціальність: є пов'язані записи");
    }

    query.prepare(R"(
        DELETE FROM speciality
        WHERE SpecialityNumber = :specialityNumber;
    )");
    query.bindValue(":specialityNumber", specialityNumber);

    tryExec(query, "deleteSpeciality");
}

QSqlQuery DatabaseManager::getSpecialityByID(int specialityNumber){
    QSqlQuery query;

    query.prepare(R"(
        SELECT
            DepartmentID,
            SpecialityName
        FROM
            speciality
        WHERE
            SpecialityNumber = :specialityNumber;
    )");
    query.bindValue(":specialityNumber", specialityNumber);
    tryExec(query, "getSpecialityByID");

    return query;
}

void DatabaseManager::addYearConfig(YearConfigData config){
    QSqlQuery query;

    query.prepare(R"(
        INSERT INTO config(ConfigYear, AnualLoad, WeakLoad, BadImbalance, CriticalImbalance) VALUES
        (:configYear, :anualLoad, :weakLoad, :badImbalance, :criticalImbalance);
    )");
    query.bindValue(":configYear", config.configYear);
    query.bindValue(":anualLoad", config.anualLoad);
    query.bindValue(":weakLoad", config.weakLoad);
    query.bindValue(":badImbalance", config.badImbalance);
    query.bindValue(":criticalImbalance", config.criticalImbalance);
    tryExec(query, "addYearConfig");
}

void DatabaseManager::updateYearConfig(YearConfigData config){
    QSqlQuery query;

    //qDebug() << "Change " << configYear << " to " << newYearConfig;

    query.prepare(R"(
        UPDATE config SET
            ConfigYear = :newYearConfig,
            AnualLoad = :anualLoad,
            WeakLoad = :weakLoad,
            BadImbalance = :badImbalance,
            CriticalImbalance = :criticalImbalance
        WHERE
            ConfigYear = :configYear;
    )");
    query.bindValue(":newYearConfig", config.newConfigYear);
    query.bindValue(":anualLoad", config.anualLoad);
    query.bindValue(":weakLoad", config.weakLoad);
    query.bindValue(":badImbalance", config.badImbalance);
    query.bindValue(":criticalImbalance", config.criticalImbalance);
    query.bindValue(":configYear", config.configYear);
    tryExec(query, "updateYearConfig");
}

int DatabaseManager::getDepartmentIdByName(QString departmentName){
    QSqlQuery query;

    query.prepare(R"(
        SELECT
            DepartmentID
        FROM
            department
        WHERE
            DepartmentName = :departmentName
    )");
    query.bindValue(":departmentName", departmentName);

    tryExec(query, "getDepartmentIdByName");

    if(query.next())
        return query.value(0).toInt();

    return -1;
}

int DatabaseManager::getOrCreateDepartment(QString departmentName){
    int departmentID = getDepartmentIdByName(departmentName);

    if(departmentID != -1)
        return departmentID;

    return addDepartment(departmentName);
}

void DatabaseManager::getOrCreateSpeciality(QString specialytiName, int specialituNumber, int departmentID){
    QSqlQuery query;

    query = getSpecialityByID(specialituNumber);
    if(query.next())
        return;

    addSpeciality(specialituNumber, departmentID, specialytiName);
}

int* DatabaseManager::getOrCreateGroup(int specialityNumber, int groupYear, int groupCount, int year, int studentQuantiti){
    int* groups = new int[groupCount]{0};

    int baseStudents = studentQuantiti / groupCount;
    int remainder = studentQuantiti % groupCount;

    QSqlQuery query;
    query.prepare(R"(
        SELECT StudentGroupID
        FROM studentgroup
        WHERE SpecialityNumber = :specialityNumber
          AND GroupYear        = :groupYear
        ORDER BY GroupNumber;
    )");
    query.bindValue(":specialityNumber", specialityNumber);
    query.bindValue(":groupYear", groupYear);

    tryExec(query, "getOrCreateGroup");

    int foundCount = 0;
    while (query.next() && foundCount < groupCount) {
        groups[foundCount++] = query.value(0).toInt();
    }

    for (int i = foundCount; i < groupCount; ++i) {
        const int subgroup = i + 1;
        const int studentsInGroup = baseStudents + (i == groupCount - 1 ? remainder : 0);

        GroupData data;

        data.specialityNumber = specialityNumber;
        data.groupYear = groupYear;
        data.subgroup = subgroup;
        data.quantityStudent = studentsInGroup;
        data.configYear = year;

        addGroup(data);

        query.prepare(R"(
            SELECT StudentGroupID
            FROM studentgroup
            WHERE SpecialityNumber = :specialityNumber
              AND GroupYear        = :groupYear
              AND GroupNumber      = :groupNumber
            LIMIT 1;
        )");
        query.bindValue(":specialityNumber", specialityNumber);
        query.bindValue(":groupYear", groupYear);
        query.bindValue(":groupNumber", subgroup);

        tryExec(query, "getOrCreateGroup selectNew");

        if (query.next()) {
            groups[i] = query.value(0).toInt();
        }
    }

    return groups;
}

int DatabaseManager::getOrCreateDiscipline(QString disciplineName){
    QSqlQuery query;

    query.prepare(R"(
        SELECT
            DisciplineID
        FROM
            discipline
        WHERE
            DisciplineName = :disciplineName;
    )");
    query.bindValue(":disciplineName", disciplineName);
    tryExec(query, "getOrCreateDiscipline");

    if(query.next())
        return query.value(0).toInt();

    return addDiscipline(disciplineName);
}

bool DatabaseManager::isGroupActivity(int activityId){
    QSqlQuery query;
    query.prepare(R"(
        SELECT IsGroupLoad
        FROM TypeActivity
        WHERE ActivityID = :activityId
        LIMIT 1
    )");
    query.bindValue(":activityId", activityId);

    tryExec(query, "isGroupActivity");

    if (!query.next()) {
        throw std::runtime_error("Невідомий тип активності");
    }

    return query.value(0).toBool();
}

QPair<QString, double> DatabaseManager::getTeacherHeaderInfo(int teacherId, int yearConfig){
    QSqlQuery query = getTeacherDataByID(teacherId, yearConfig);

    if (!query.next())
        throw std::runtime_error("TEACHER_NOT_FOUND");

    return {
        query.value("PIB").toString().trimmed(),
        query.value("Rate").toDouble()
    };
}

QSqlQuery DatabaseManager::getExportTeacherLoad(int teacherId, int yearConfig){
    QSqlQuery query(db);

    query.prepare(R"(
        SELECT
            da.Semester,
            d.DisciplineName,
            da.GeneralTime,
            da.ActivityID,
            s.SpecialityName,

            CASE
                WHEN da.QuantityStudent IS NOT NULL THEN da.QuantityStudent

                WHEN ta.IsGroupLoad = FALSE THEN (
                    SELECT SUM(qs.QuantityStudent)
                    FROM StudentGroup sg2
                    JOIN QuantityStudentOnGroup qs
                        ON qs.StudentGroupID = sg2.StudentGroupID
                    WHERE sg2.SpecialityNumber = sg.SpecialityNumber
                      AND qs.SettingsYear = da.DisciplineYear
                      AND sg2.GroupYear = sg.GroupYear
                )

                ELSE qsg.QuantityStudent
            END AS StudentsQuantity

        FROM TeachingLoad ty
        JOIN DisciplineActivity da
            ON ty.DisciplineActivityID = da.DisciplineActivity
        JOIN Discipline d
            ON da.DisciplineID = d.DisciplineID
        JOIN StudentGroup sg
            ON da.StudentGroupID = sg.StudentGroupID
        JOIN Speciality s
            ON sg.SpecialityNumber = s.SpecialityNumber
        JOIN QuantityStudentOnGroup qsg
            ON sg.StudentGroupID = qsg.StudentGroupID
           AND qsg.SettingsYear = :year
        JOIN TypeActivity ta
            ON da.ActivityID = ta.ActivityID

        WHERE ty.TecherID = :teacherId
          AND da.DisciplineYear = :year

        ORDER BY da.Semester, d.DisciplineName, da.ActivityID
    )"); // ORDER BY da.Semester, d.DisciplineName, da.ActivityID - it`s CRITICALLY important that the program considers that the data must be sorted

    query.bindValue(":teacherId", teacherId);
    query.bindValue(":year", yearConfig);

    tryExec(query, "getExportTeacherLoad");
    return query;
}

int DatabaseManager::getPostId(int teacherId){
    QSqlQuery query;

    query.prepare(R"(
        SELECT
            PostID
        FROM
            teacher
        WHERE
            TecherID = :teacherId
    )");
    query.bindValue(":teacherId", teacherId);

    tryExec(query, "getPostId");

    if (!query.next()) {
        std::runtime_error("Викладача не знайдено");
    }

    return query.value(0).toInt();
}

int DatabaseManager::getActivityId(int disciplyneId){
    QSqlQuery query;

    query.prepare(R"(
        SELECT
            ActivityID
        FROM
            disciplineactivity
        WHERE
            DisciplineActivity = :disciplyneId
    )");
    query.bindValue(":disciplyneId", disciplyneId);

    tryExec(query, "getActivityId");

    if (!query.next()) {
        throw std::runtime_error("Активність не знайдено");
    }

    return query.value(0).toInt();
}