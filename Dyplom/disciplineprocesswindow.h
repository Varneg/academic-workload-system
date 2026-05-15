#ifndef DISCIPLINEPROCESSWINDOW_H
#define DISCIPLINEPROCESSWINDOW_H

#include <QDialog>
#include "uiUtils.h"
#include "databasemanager.h"
#include "datamodels.h"

namespace Ui {
class DisciplineProcessWindow;
}

class DisciplineProcessWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DisciplineProcessWindow(QWidget *parent = nullptr, enum WindowType = WindowType::Adding, int configYear = -1, int id = -1);
    ~DisciplineProcessWindow();

private:
    QPoint m_dragPosition;
    Ui::DisciplineProcessWindow *ui;
    DatabaseManager* dbManager;
    enum WindowType wT;
    int m_configYear;

    void addDisciplineActivity();
    void edditDisciplineActivity();
    void unblockAllWidget();
    void validation();
    DisciplineActivityData getDisciplineActivityDataFromUI();
    void validateActivityData(DisciplineActivityData data);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_closeButton_clicked();
    void on_cancelButon_clicked();
    void on_agreeButton_clicked();
    void on_typeDisciplineComboBox_currentIndexChanged(int index);
};

#endif // DISCIPLINEPROCESSWINDOW_H
