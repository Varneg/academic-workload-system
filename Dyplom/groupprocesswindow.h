#ifndef GROUPPROCESSWINDOW_H
#define GROUPPROCESSWINDOW_H

#include <QDialog>
#include "uiUtils.h"
#include "databasemanager.h"
#include "datamodels.h"

namespace Ui {
class GroupProcessWindow;
}

class GroupProcessWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GroupProcessWindow(QWidget *parent = nullptr, enum WindowType = WindowType::Adding, int year = -1, int studentGroupID = -1);
    ~GroupProcessWindow();

private:
    QPoint m_dragPosition;
    Ui::GroupProcessWindow *ui;
    DatabaseManager* dbManager;
    enum WindowType wT;
    int configYear;

    void addGroup();
    void editGroup();
    void validation();
    void validateGroupData(GroupData data);
    GroupData getGroupDataFromUI();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_closeButton_clicked();
    void on_cancelButon_clicked();
    void on_agreeButton_clicked();
};

#endif // GROUPPROCESSWINDOW_H
