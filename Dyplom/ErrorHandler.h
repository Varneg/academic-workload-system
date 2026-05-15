#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QWidget>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include "databasemanager.h"

class ErrorHandler {
public:
    static void showError(QWidget* parent, const QString& userMessage, const std::exception& e, const QString& title = "Помилка"){
        QString errorText = e.what();

        qCritical() << errorText;

        QMessageBox msg(parent);
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle(title);

        if (errorText == "DB_CONNECTION_LOST") {
            msg.setText("Втрачено з'єднання з базою даних.\nСпробувати перепідключитися?");
            msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

            if (msg.exec() == QMessageBox::Yes) {
                attemptReconnect(parent);
            } else {
                QApplication::quit();
            }
            return;
        }

        msg.setText(userMessage);
        msg.setDetailedText(errorText);
        msg.exec();
    }

private:
    static void attemptReconnect(QWidget* parent){
        try {
            DatabaseManager::instance().reconnect();
        } catch (...) {
            QMessageBox::critical(parent, "Помилка", "Не вдалося перепідключитися");
            QApplication::quit();
        }
    }
};

#endif // ERRORHANDLER_H
