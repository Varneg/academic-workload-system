/********************************************************************************
** Form generated from reading UI file 'specialityprocesswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPECIALITYPROCESSWINDOW_H
#define UI_SPECIALITYPROCESSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <editablecombobox.h>

QT_BEGIN_NAMESPACE

class Ui_SpecialityProcessWindow
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *Headar;
    QHBoxLayout *horizontalLayout;
    QLabel *windowTitle;
    QToolButton *closeButton;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    EditableComboBox *departmentComboBox;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame_8;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *specialityNameLineEdit;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_5;
    QFrame *frame_7;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *specialityNumberLineEdit;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButon;
    QPushButton *agreeButton;

    void setupUi(QDialog *SpecialityProcessWindow)
    {
        if (SpecialityProcessWindow->objectName().isEmpty())
            SpecialityProcessWindow->setObjectName("SpecialityProcessWindow");
        SpecialityProcessWindow->resize(682, 563);
        SpecialityProcessWindow->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(139, 139, 139);"));
        verticalLayout = new QVBoxLayout(SpecialityProcessWindow);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Headar = new QFrame(SpecialityProcessWindow);
        Headar->setObjectName("Headar");
        Headar->setMaximumSize(QSize(16777215, 54));
        Headar->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(139, 139, 139);"));
        Headar->setFrameShape(QFrame::Shape::StyledPanel);
        Headar->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(Headar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        windowTitle = new QLabel(Headar);
        windowTitle->setObjectName("windowTitle");
        windowTitle->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        windowTitle->setStyleSheet(QString::fromUtf8("color: black;\n"
"border: 0px;\n"
"margin-left: 24px;\n"
"margin-bottom: 6px;\n"
"font: 26px;\n"
"font-weight: 700;"));
        windowTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(windowTitle);

        closeButton = new QToolButton(Headar);
        closeButton->setObjectName("closeButton");
        closeButton->setStyleSheet(QString::fromUtf8("border: 0px;"));

        horizontalLayout->addWidget(closeButton);


        verticalLayout->addWidget(Headar);

        frame = new QFrame(SpecialityProcessWindow);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("border: 0px;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame_3 = new QFrame(frame);
        frame_3->setObjectName("frame_3");
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_3);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(-1, -1, -1, 0);
        frame_6 = new QFrame(frame_3);
        frame_6->setObjectName("frame_6");
        frame_6->setStyleSheet(QString::fromUtf8("color: rgb(223, 33, 33);"));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_6);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(frame_6);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777215, 39));
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 20px;\n"
"font-weight: 700;"));

        horizontalLayout_3->addWidget(label);

        label_4 = new QLabel(frame_6);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 20px;\n"
"font-weight: 700;\n"
"color: rgb(223, 33, 33);"));

        horizontalLayout_3->addWidget(label_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addWidget(frame_6);

        departmentComboBox = new EditableComboBox(frame_3);
        departmentComboBox->setObjectName("departmentComboBox");
        departmentComboBox->setMinimumSize(QSize(0, 45));
        departmentComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid rgb(139, 139, 139);\n"
"border-radius: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font-size: 14px;"));

        verticalLayout_3->addWidget(departmentComboBox);


        verticalLayout_2->addWidget(frame_3);

        frame_5 = new QFrame(frame);
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
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 20px;\n"
"font-weight: 700;"));

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

        specialityNameLineEdit = new QLineEdit(frame_5);
        specialityNameLineEdit->setObjectName("specialityNameLineEdit");
        specialityNameLineEdit->setMinimumSize(QSize(0, 45));
        specialityNameLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid rgb(139, 139, 139);\n"
"border-radius: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font-size: 14px;"));

        verticalLayout_4->addWidget(specialityNameLineEdit);


        verticalLayout_2->addWidget(frame_5);

        frame_4 = new QFrame(frame);
        frame_4->setObjectName("frame_4");
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_4);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(-1, 0, -1, -1);
        frame_7 = new QFrame(frame_4);
        frame_7->setObjectName("frame_7");
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_7);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        label_3 = new QLabel(frame_7);
        label_3->setObjectName("label_3");
        label_3->setMaximumSize(QSize(16777215, 39));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 20px;\n"
"font-weight: 700;"));

        horizontalLayout_4->addWidget(label_3);

        label_2 = new QLabel(frame_7);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 20px;\n"
"font-weight: 700;\n"
"color: rgb(223, 33, 33);"));

        horizontalLayout_4->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_5->addWidget(frame_7);

        specialityNumberLineEdit = new QLineEdit(frame_4);
        specialityNumberLineEdit->setObjectName("specialityNumberLineEdit");
        specialityNumberLineEdit->setMinimumSize(QSize(0, 45));
        specialityNumberLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid rgb(139, 139, 139);\n"
"border-radius: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font-size: 14px;"));

        verticalLayout_5->addWidget(specialityNumberLineEdit);


        verticalLayout_2->addWidget(frame_4);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(SpecialityProcessWindow);
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


        retranslateUi(SpecialityProcessWindow);

        QMetaObject::connectSlotsByName(SpecialityProcessWindow);
    } // setupUi

    void retranslateUi(QDialog *SpecialityProcessWindow)
    {
        SpecialityProcessWindow->setWindowTitle(QCoreApplication::translate("SpecialityProcessWindow", "Dialog", nullptr));
        windowTitle->setText(QString());
        closeButton->setText(QCoreApplication::translate("SpecialityProcessWindow", "...", nullptr));
        label->setText(QCoreApplication::translate("SpecialityProcessWindow", "\320\232\320\260\321\204\320\265\320\264\321\200\320\260", nullptr));
        label_4->setText(QCoreApplication::translate("SpecialityProcessWindow", "*", nullptr));
        label_6->setText(QCoreApplication::translate("SpecialityProcessWindow", "\320\235\320\260\320\267\320\262\320\260 \321\201\320\277\320\265\321\206\321\226\320\260\320\273\321\214\320\275\320\276\321\201\321\202\321\226", nullptr));
        label_7->setText(QCoreApplication::translate("SpecialityProcessWindow", "*", nullptr));
        specialityNameLineEdit->setText(QString());
        label_3->setText(QCoreApplication::translate("SpecialityProcessWindow", "\320\235\320\276\320\274\320\265\321\200 \321\201\320\277\320\265\321\206\321\226\320\260\320\273\321\214\320\275\320\276\321\201\321\202\321\226", nullptr));
        label_2->setText(QCoreApplication::translate("SpecialityProcessWindow", "*", nullptr));
        specialityNumberLineEdit->setText(QString());
        cancelButon->setText(QCoreApplication::translate("SpecialityProcessWindow", "\320\241\320\272\320\260\321\201\321\203\320\262\320\260\321\202\320\270", nullptr));
        agreeButton->setText(QCoreApplication::translate("SpecialityProcessWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpecialityProcessWindow: public Ui_SpecialityProcessWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPECIALITYPROCESSWINDOW_H
