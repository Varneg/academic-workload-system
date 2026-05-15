// This is a file that contains global Ui functions.

#ifndef UIUTILS_H
#define UIUTILS_H

#include <QString>
#include <QAbstractButton>
#include <QPushButton>
#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QFile>
#include <QMessageBox>
#include <QComboBox>

const QString BUTON_STYLE_FILE = ":/cssStyle/style/butonStyle.qss";
const QString TAB_WIDGET_STYLE_FILE = ":/cssStyle/style/tabWidgetStyle.qss";

enum class WindowType {
    Editing,
    Adding
};

namespace UiUtils {
    void setIconOnButton(const QString &pathToIcon, QAbstractButton *button);
    const QString readStyleFile(QWidget *parent, const QString &pathToStyleFile);
    void setStandardButtonStyle(QWidget *parent, const QString &style);
    void setShadow(QWidget *widget);
    void setShadowOnAllPushButtons(QWidget *parent);
    float parseOrMinusOne(const QVariant& v);
    QString parseOrNull(const QVariant& v);
    void blockWidget(QWidget *widget);
    void unblockWidget(QWidget *widget);
}

#endif // UIUTILS_H
