/********************************************************************************
** Form generated from reading UI file 'exportwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTWINDOW_H
#define UI_EXPORTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <editablecombobox.h>

QT_BEGIN_NAMESPACE

class Ui_exportwindow
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame_8;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_4;
    EditableComboBox *teacherComboBox;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *chooseFileLineEdit;
    QPushButton *chooseFilePushButton;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButon;
    QPushButton *agreeButton;

    void setupUi(QDialog *exportwindow)
    {
        if (exportwindow->objectName().isEmpty())
            exportwindow->setObjectName("exportwindow");
        exportwindow->resize(426, 213);
        verticalLayout = new QVBoxLayout(exportwindow);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame_5 = new QFrame(exportwindow);
        frame_5->setObjectName("frame_5");
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_5);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        frame_8 = new QFrame(frame_5);
        frame_8->setObjectName("frame_8");
        frame_8->setStyleSheet(QString::fromUtf8("color: rgb(223, 33, 33);"));
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_8);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(frame_8);
        label_6->setObjectName("label_6");
        label_6->setMaximumSize(QSize(16777215, 39));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        horizontalLayout_5->addWidget(label_6);

        label_7 = new QLabel(frame_8);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 20px;\n"
"font-weight: 700;\n"
"color: rgb(223, 33, 33);"));

        horizontalLayout_5->addWidget(label_7);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_4->addWidget(frame_8);

        teacherComboBox = new EditableComboBox(frame_5);
        teacherComboBox->setObjectName("teacherComboBox");
        teacherComboBox->setMinimumSize(QSize(0, 45));
        teacherComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid rgb(139, 139, 139);\n"
"border-radius: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font-size: 14px;"));

        verticalLayout_4->addWidget(teacherComboBox);


        verticalLayout->addWidget(frame_5);

        frame = new QFrame(exportwindow);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        chooseFileLineEdit = new QLineEdit(frame);
        chooseFileLineEdit->setObjectName("chooseFileLineEdit");

        horizontalLayout_3->addWidget(chooseFileLineEdit);

        chooseFilePushButton = new QPushButton(frame);
        chooseFilePushButton->setObjectName("chooseFilePushButton");

        horizontalLayout_3->addWidget(chooseFilePushButton);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(exportwindow);
        frame_2->setObjectName("frame_2");
        frame_2->setMaximumSize(QSize(16777215, 54));
        frame_2->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(139, 139, 139);"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cancelButon = new QPushButton(frame_2);
        cancelButon->setObjectName("cancelButon");
        cancelButon->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        horizontalLayout_2->addWidget(cancelButon);

        agreeButton = new QPushButton(frame_2);
        agreeButton->setObjectName("agreeButton");
        agreeButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(60, 140, 206);"));

        horizontalLayout_2->addWidget(agreeButton);


        verticalLayout->addWidget(frame_2);


        retranslateUi(exportwindow);

        QMetaObject::connectSlotsByName(exportwindow);
    } // setupUi

    void retranslateUi(QDialog *exportwindow)
    {
        exportwindow->setWindowTitle(QCoreApplication::translate("exportwindow", "Dialog", nullptr));
        label_6->setText(QCoreApplication::translate("exportwindow", "\320\236\320\261\320\265\321\200\321\226\321\202\321\214 \320\262\320\270\320\272\320\273\320\260\320\264\320\260\321\207\320\260", nullptr));
        label_7->setText(QCoreApplication::translate("exportwindow", "*", nullptr));
        label_2->setText(QCoreApplication::translate("exportwindow", "\320\236\320\261\320\265\321\200\321\226\321\202\321\214\320\261 \321\204\320\260\320\271\320\273  ", nullptr));
        chooseFilePushButton->setText(QCoreApplication::translate("exportwindow", "\320\236\320\261\321\200\320\260\321\202\320\270 \321\204\320\260\320\271\320\273", nullptr));
        cancelButon->setText(QCoreApplication::translate("exportwindow", "\320\241\320\272\320\260\321\201\321\203\320\262\320\260\321\202\320\270", nullptr));
        agreeButton->setText(QCoreApplication::translate("exportwindow", "\320\225\320\272\321\201\320\277\320\276\321\200\321\202\321\203\320\262\320\260\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class exportwindow: public Ui_exportwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTWINDOW_H
