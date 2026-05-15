#ifndef TEACHERPROCESSWINDOW_H
#define TEACHERPROCESSWINDOW_H

#include <QDialog>
#include "uiUtils.h"
#include "databasemanager.h"
#include "datamodels.h"

namespace Ui {
class TeacherProcessWindow;
}

class TeacherProcessWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TeacherProcessWindow(QWidget *parent = nullptr, enum WindowType wT = WindowType::Adding, int id = -1, int configYear = -1);
    ~TeacherProcessWindow();

private:
    enum WindowType wT;

    QPoint m_dragPosition;
    Ui::TeacherProcessWindow *ui;
    DatabaseManager* dbManager;
    int currentPostID = -1;
    void validation();
    void addTeacher();
    void editTeacher();
    void validateTeacherData(const QString& PIB, const int postID);
    TeacherData getTeacherDataFromUI();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_closeButton_clicked();
    void on_cancelButon_clicked();
    void on_agreeButton_clicked();
};

#endif // TEACHERPROCESSWINDOW_H
