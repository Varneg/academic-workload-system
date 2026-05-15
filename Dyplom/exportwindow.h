#ifndef EXPORTWINDOW_H
#define EXPORTWINDOW_H

#include <QDialog>
#include "databasemanager.h"

namespace Ui {
class exportwindow;
}

class exportwindow : public QDialog
{
    Q_OBJECT

public:
    explicit exportwindow(QWidget *parent = nullptr, int configYear = -1);
    ~exportwindow();

private slots:
    void on_chooseFilePushButton_clicked();

    void on_agreeButton_clicked();

private:
    Ui::exportwindow *ui;
    DatabaseManager* dbManager;
    int year;
};

#endif // EXPORTWINDOW_H
