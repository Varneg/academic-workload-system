#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QStandardItemModel>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QSqlTableModel>

#include "databasemanager.h"
#include "buttondelegate.h"

#define TABLE_VIEW_STYLE_FILE ":/cssStyle/style/tableViewStyle.qss"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void changeFooterPage(int index);
    void on_addTeacherButton_clicked();
    void on_addNewYearButton_clicked();
    void on_setteningButton_clicked();
    void on_addDisciplineButton_clicked();
    void on_addGroupButton_clicked();
    void on_addSpecialityButton_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_configYearComboBox_currentIndexChanged(int index);
    void on_deleatButton_clicked();
    void on_importButton_clicked();
    void on_exportButton_clicked();

private:
    struct config
    {
        int currentYear;
        int anualLoad;
        int weakLoad;
        int badImbalance;
        int criticalImbalance;
    };

    QSortFilterProxyModel *teacherProxy;
    QSqlTableModel *teacherModel;

    QSortFilterProxyModel *disciplineProxy;
    QSqlTableModel *disciplineModel;

    QSortFilterProxyModel *groupProxy;
    QSqlTableModel *groupModel;

    QHash<TableType, ButtonDelegate*> m_delegates;
    bool m_deleteMode = false;

    config currentConfig;
    void resizeFooter();
    void writeTeacherData();
    DatabaseManager* dbManager;
    void initDatabase();
    void fillConfigYearComboBox();
    void setConfig(int year);
    QStandardItem* makeItem(const QVariant &value);
    void setupTableView(QTableView *tableView, int hidenColumn = -1);
    void setupDelegate(QTableView *tableView, QStandardItemModel* model, int column, TableType type);
    void writeLoadData();
    void writeGroupData();
    void writeSpecialityData();
    void setAllDelegatesMode(ActionMode mode);
    void updateTableOnPage(int index);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
