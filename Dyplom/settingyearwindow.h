#ifndef SETTINGYEARWINDOW_H
#define SETTINGYEARWINDOW_H

#include <QDialog>
#include "uiUtils.h"
#include "databasemanager.h"
#include "datamodels.h"

namespace Ui {
class SettingYearWindow;
}

class SettingYearWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingYearWindow(QWidget *parent = nullptr, enum WindowType winType = WindowType::Adding, int configYear = -1);
    ~SettingYearWindow();

private:
    QPoint m_dragPosition;
    Ui::SettingYearWindow *ui;
    DatabaseManager* dbManager;
    enum WindowType wT;

    void addConfig();
    void editConfig();
    void validation();
    void validateConfigData(YearConfigData data);
    YearConfigData getYearConfigFromUI();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_closeButton_clicked();
    void on_cancelButon_clicked();
    void on_agreeButton_clicked();
};

#endif // SETTINGYEARWINDOW_H
