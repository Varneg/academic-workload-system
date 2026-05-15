#include "uiUtils.h"
#include <QIcon>
#include <QPushButton>
#include <qabstractbutton.h>
#include <QDebug>
#include <QCompleter>


namespace UiUtils {
    void setIconOnButton(const QString &pathToIcon, QAbstractButton *button){
        int h = button->height() * 0.75;
        button->setIcon(QIcon(pathToIcon));
        button->setIconSize(QSize(h, h));
        button->setLayoutDirection(Qt::LeftToRight);
    }

    const QString readStyleFile(QWidget *parent, const QString &pathToStyleFile) {
        QFile file(pathToStyleFile);
        if(!file.open(QFile::ReadOnly)){
            QMessageBox::information(parent, "Помилка завантаження файлу стилів",
                                     "Файл зі стилями не знайдено. Деякі елементи можуть мати некоректний вигляд!");
            return ""; //standart style
        } else {
            return file.readAll();
        }
    }

    void setStandardButtonStyle(QWidget *parent, const QString &style) {
        QList<QPushButton*> buttons = parent->findChildren<QPushButton*>();
        for(QPushButton* btn : buttons){
            btn->setStyleSheet(style);
        }
    }

    void setShadow(QWidget *widget) {
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(widget);
        shadow->setBlurRadius(15);
        shadow->setOffset(0, 5);
        shadow->setColor(QColor(0, 0, 0, 75));
        widget->setGraphicsEffect(shadow);
    }

    void setShadowOnAllPushButtons(QWidget *parent) {
        QList<QPushButton*> buttons = parent->findChildren<QPushButton*>();
        for (QPushButton* btn : buttons){
            setShadow(btn);
        }
    }

    float parseOrMinusOne(const QVariant& v) {
        if (!v.isValid() || v.isNull())
            return -1;

        bool ok = false;
        float value = v.toFloat(&ok);

        return ok ? value : -1;
    }

    QString parseOrNull(const QVariant& v) {
        if (!v.isValid() || v.isNull())
            return QString();

        QString s = v.toString().trimmed();

        return s.isEmpty() ? QString() : s;
    }

    void blockWidget(QWidget *widget){
        widget->setEnabled(false);
        widget->setStyleSheet(R"(background-color: #e0e0e0;
                              color: #666666;
                              border: 1px solid #b0b0b0;
                              border-radius: 5px;
                              )");
    }

    void unblockWidget(QWidget *widget){
        widget->setEnabled(true);
        widget->setStyleSheet(R"(background-color: rgb(255, 255, 255);
                              border: 1px solid rgb(139, 139, 139);
                              border-radius: 5px;
                              color: rgb(0, 0, 0);)");
    }
}
