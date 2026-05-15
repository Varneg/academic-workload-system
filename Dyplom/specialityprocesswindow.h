#ifndef SPECIALITYPROCESSWINDOW_H
#define SPECIALITYPROCESSWINDOW_H

#include <QDialog>
#include "uiUtils.h"
#include "databasemanager.h"
#include "datamodels.h"

namespace Ui {
class SpecialityProcessWindow;
}

class SpecialityProcessWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SpecialityProcessWindow(QWidget *parent = nullptr, enum WindowType wT = WindowType::Adding, int specialityNumber = -1);
    ~SpecialityProcessWindow();

private:
    QPoint m_dragPosition;
    Ui::SpecialityProcessWindow *ui;
    DatabaseManager* dbManager;
    enum WindowType wT;

    void addSpeciality();
    void editSpeciality();
    void validation();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_closeButton_clicked();
    void on_cancelButon_clicked();
    void on_agreeButton_clicked();
};

#endif // SPECIALITYPROCESSWINDOW_H
