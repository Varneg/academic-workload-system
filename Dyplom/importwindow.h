#ifndef IMPORTWINDOW_H
#define IMPORTWINDOW_H

#include <QDialog>

namespace Ui {
class ImportWindow;
}

class ImportWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ImportWindow(QWidget *parent = nullptr, int curentYear = -1);
    ~ImportWindow();

private slots:
    void on_chooseFilePushButton_clicked();
    void on_cancelButon_clicked();

    void on_agreeButton_clicked();

private:
    Ui::ImportWindow *ui;
    int year;

    void import();
};

#endif // IMPORTWINDOW_H
