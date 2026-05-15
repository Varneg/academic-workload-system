/********************************************************************************
** Form generated from reading UI file 'disciplineprocesswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISCIPLINEPROCESSWINDOW_H
#define UI_DISCIPLINEPROCESSWINDOW_H

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

class Ui_DisciplineProcessWindow
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
    EditableComboBox *disciplineComboBox;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame_8;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_4;
    EditableComboBox *typeDisciplineComboBox;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_5;
    QFrame *frame_9;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_5;
    EditableComboBox *groupComboBox;
    QFrame *frame_13;
    QVBoxLayout *verticalLayout_16;
    QFrame *frame_24;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_19;
    EditableComboBox *teacherComboBox;
    QFrame *frame_14;
    QHBoxLayout *horizontalLayout_7;
    QFrame *frame_10;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_3;
    QLineEdit *totalHourLineEdit;
    QFrame *frame_11;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_5;
    QLineEdit *hourPerWeakLineEdit;
    QFrame *frame_7;
    QHBoxLayout *horizontalLayout_4;
    QFrame *frame_12;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_10;
    QLineEdit *semestrLineEdit;
    QFrame *frame_15;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_11;
    QLineEdit *quantityStudent;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButon;
    QPushButton *agreeButton;

    void setupUi(QDialog *DisciplineProcessWindow)
    {
        if (DisciplineProcessWindow->objectName().isEmpty())
            DisciplineProcessWindow->setObjectName("DisciplineProcessWindow");
        DisciplineProcessWindow->resize(731, 844);
        DisciplineProcessWindow->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(139, 139, 139);"));
        verticalLayout = new QVBoxLayout(DisciplineProcessWindow);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Headar = new QFrame(DisciplineProcessWindow);
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

        frame = new QFrame(DisciplineProcessWindow);
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

        disciplineComboBox = new EditableComboBox(frame_3);
        disciplineComboBox->setObjectName("disciplineComboBox");
        disciplineComboBox->setMinimumSize(QSize(0, 45));
        disciplineComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid rgb(139, 139, 139);\n"
"border-radius: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font-size: 14px;"));

        verticalLayout_3->addWidget(disciplineComboBox);


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

        typeDisciplineComboBox = new EditableComboBox(frame_5);
        typeDisciplineComboBox->setObjectName("typeDisciplineComboBox");
        typeDisciplineComboBox->setMinimumSize(QSize(0, 45));
        typeDisciplineComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid rgb(139, 139, 139);\n"
"border-radius: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font-size: 14px;"));

        verticalLayout_4->addWidget(typeDisciplineComboBox);


        verticalLayout_2->addWidget(frame_5);

        frame_4 = new QFrame(frame);
        frame_4->setObjectName("frame_4");
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_4);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        frame_9 = new QFrame(frame_4);
        frame_9->setObjectName("frame_9");
        frame_9->setStyleSheet(QString::fromUtf8("color: rgb(223, 33, 33);"));
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_9);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(frame_9);
        label_8->setObjectName("label_8");
        label_8->setMaximumSize(QSize(16777215, 39));
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 20px;\n"
"font-weight: 700;"));

        horizontalLayout_6->addWidget(label_8);

        label_9 = new QLabel(frame_9);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 20px;\n"
"font-weight: 700;\n"
"color: rgb(223, 33, 33);"));

        horizontalLayout_6->addWidget(label_9);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout_5->addWidget(frame_9);

        groupComboBox = new EditableComboBox(frame_4);
        groupComboBox->setObjectName("groupComboBox");
        groupComboBox->setMinimumSize(QSize(0, 45));
        groupComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid rgb(139, 139, 139);\n"
"border-radius: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font-size: 14px;"));

        verticalLayout_5->addWidget(groupComboBox);


        verticalLayout_2->addWidget(frame_4);

        frame_13 = new QFrame(frame);
        frame_13->setObjectName("frame_13");
        frame_13->setFrameShape(QFrame::Shape::StyledPanel);
        frame_13->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_16 = new QVBoxLayout(frame_13);
        verticalLayout_16->setObjectName("verticalLayout_16");
        frame_24 = new QFrame(frame_13);
        frame_24->setObjectName("frame_24");
        frame_24->setFrameShape(QFrame::Shape::StyledPanel);
        frame_24->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_11 = new QHBoxLayout(frame_24);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_19 = new QLabel(frame_24);
        label_19->setObjectName("label_19");
        label_19->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 20px;\n"
"font-weight: 700;"));

        horizontalLayout_11->addWidget(label_19);


        verticalLayout_16->addWidget(frame_24);

        teacherComboBox = new EditableComboBox(frame_13);
        teacherComboBox->setObjectName("teacherComboBox");
        teacherComboBox->setMinimumSize(QSize(0, 45));
        teacherComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid rgb(139, 139, 139);\n"
"border-radius: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font-size: 14px;"));

        verticalLayout_16->addWidget(teacherComboBox);


        verticalLayout_2->addWidget(frame_13);

        frame_14 = new QFrame(frame);
        frame_14->setObjectName("frame_14");
        frame_14->setFrameShape(QFrame::Shape::StyledPanel);
        frame_14->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_7 = new QHBoxLayout(frame_14);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(-1, 0, -1, 0);
        frame_10 = new QFrame(frame_14);
        frame_10->setObjectName("frame_10");
        frame_10->setFrameShape(QFrame::Shape::StyledPanel);
        frame_10->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_10);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(-1, 0, -1, 0);
        label_3 = new QLabel(frame_10);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(0, 76));
        label_3->setMaximumSize(QSize(16777215, 39));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 20px;\n"
"font-weight: 700;"));
        label_3->setWordWrap(true);

        verticalLayout_6->addWidget(label_3);

        totalHourLineEdit = new QLineEdit(frame_10);
        totalHourLineEdit->setObjectName("totalHourLineEdit");
        totalHourLineEdit->setMinimumSize(QSize(0, 45));
        totalHourLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid rgb(139, 139, 139);\n"
"border-radius: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font-size: 14px;"));

        verticalLayout_6->addWidget(totalHourLineEdit);


        horizontalLayout_7->addWidget(frame_10);

        frame_11 = new QFrame(frame_14);
        frame_11->setObjectName("frame_11");
        frame_11->setFrameShape(QFrame::Shape::StyledPanel);
        frame_11->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_11);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(-1, 0, -1, 0);
        label_5 = new QLabel(frame_11);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(0, 76));
        label_5->setMaximumSize(QSize(16777215, 39));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 20px;\n"
"font-weight: 700;"));
        label_5->setWordWrap(true);

        verticalLayout_7->addWidget(label_5);

        hourPerWeakLineEdit = new QLineEdit(frame_11);
        hourPerWeakLineEdit->setObjectName("hourPerWeakLineEdit");
        hourPerWeakLineEdit->setMinimumSize(QSize(0, 45));
        hourPerWeakLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid rgb(139, 139, 139);\n"
"border-radius: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font-size: 14px;"));

        verticalLayout_7->addWidget(hourPerWeakLineEdit);


        horizontalLayout_7->addWidget(frame_11);


        verticalLayout_2->addWidget(frame_14);

        frame_7 = new QFrame(frame);
        frame_7->setObjectName("frame_7");
        frame_7->setMinimumSize(QSize(0, 182));
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_7);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, -1, 0);
        frame_12 = new QFrame(frame_7);
        frame_12->setObjectName("frame_12");
        frame_12->setFrameShape(QFrame::Shape::StyledPanel);
        frame_12->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_8 = new QVBoxLayout(frame_12);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(-1, 0, -1, -1);
        label_10 = new QLabel(frame_12);
        label_10->setObjectName("label_10");
        label_10->setMinimumSize(QSize(0, 76));
        label_10->setMaximumSize(QSize(16777215, 39));
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 20px;\n"
"font-weight: 700;"));
        label_10->setWordWrap(true);

        verticalLayout_8->addWidget(label_10);

        semestrLineEdit = new QLineEdit(frame_12);
        semestrLineEdit->setObjectName("semestrLineEdit");
        semestrLineEdit->setMinimumSize(QSize(0, 45));
        semestrLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid rgb(139, 139, 139);\n"
"border-radius: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font-size: 14px;"));

        verticalLayout_8->addWidget(semestrLineEdit);


        horizontalLayout_4->addWidget(frame_12);

        frame_15 = new QFrame(frame_7);
        frame_15->setObjectName("frame_15");
        frame_15->setFrameShape(QFrame::Shape::StyledPanel);
        frame_15->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_9 = new QVBoxLayout(frame_15);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(-1, 0, -1, -1);
        label_11 = new QLabel(frame_15);
        label_11->setObjectName("label_11");
        label_11->setMinimumSize(QSize(0, 76));
        label_11->setMaximumSize(QSize(16777215, 39));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 20px;\n"
"font-weight: 700;"));
        label_11->setWordWrap(true);

        verticalLayout_9->addWidget(label_11);

        quantityStudent = new QLineEdit(frame_15);
        quantityStudent->setObjectName("quantityStudent");
        quantityStudent->setMinimumSize(QSize(0, 45));
        quantityStudent->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid rgb(139, 139, 139);\n"
"border-radius: 5px;\n"
"color: rgb(0, 0, 0);\n"
"font-size: 14px;"));

        verticalLayout_9->addWidget(quantityStudent);


        horizontalLayout_4->addWidget(frame_15);


        verticalLayout_2->addWidget(frame_7);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(DisciplineProcessWindow);
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


        retranslateUi(DisciplineProcessWindow);

        QMetaObject::connectSlotsByName(DisciplineProcessWindow);
    } // setupUi

    void retranslateUi(QDialog *DisciplineProcessWindow)
    {
        DisciplineProcessWindow->setWindowTitle(QCoreApplication::translate("DisciplineProcessWindow", "Dialog", nullptr));
        windowTitle->setText(QString());
        closeButton->setText(QCoreApplication::translate("DisciplineProcessWindow", "...", nullptr));
        label->setText(QCoreApplication::translate("DisciplineProcessWindow", "\320\235\320\260\320\267\320\262\320\260 \320\264\320\270\321\201\321\206\320\270\320\277\320\273\321\226\320\275\320\270", nullptr));
        label_4->setText(QCoreApplication::translate("DisciplineProcessWindow", "*", nullptr));
        label_6->setText(QCoreApplication::translate("DisciplineProcessWindow", "\320\242\320\270\320\277 \320\267\320\260\320\275\321\217\321\202\321\202\321\217", nullptr));
        label_7->setText(QCoreApplication::translate("DisciplineProcessWindow", "*", nullptr));
        label_8->setText(QCoreApplication::translate("DisciplineProcessWindow", "\320\223\321\200\321\203\320\277\320\260", nullptr));
        label_9->setText(QCoreApplication::translate("DisciplineProcessWindow", "*", nullptr));
        label_19->setText(QCoreApplication::translate("DisciplineProcessWindow", "\320\222\320\270\320\272\320\273\320\260\320\264\320\260\321\207", nullptr));
        label_3->setText(QCoreApplication::translate("DisciplineProcessWindow", "\320\227\320\260\320\263\320\260\320\273\321\214\320\275\320\260 \320\272\321\226\320\273\321\214\320\272\321\226\321\201\321\202\321\214 \320\263\320\276\320\264\320\270\320\275", nullptr));
        totalHourLineEdit->setText(QString());
        label_5->setText(QCoreApplication::translate("DisciplineProcessWindow", "\320\232\321\226\320\273\321\214\320\272\321\226\321\201\321\202\321\214 \320\263\320\276\320\264\320\270\320\275 \320\275\320\260 \321\202\320\270\320\266\320\264\320\265\320\275\321\214", nullptr));
        hourPerWeakLineEdit->setText(QString());
        label_10->setText(QCoreApplication::translate("DisciplineProcessWindow", "\320\241\320\265\320\274\320\265\321\201\321\202\321\200", nullptr));
        semestrLineEdit->setText(QString());
        label_11->setText(QCoreApplication::translate("DisciplineProcessWindow", "\320\232\321\226\320\273\321\214\320\272\321\226\321\201\321\202\321\214 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\321\226\320\262", nullptr));
        quantityStudent->setText(QString());
        cancelButon->setText(QCoreApplication::translate("DisciplineProcessWindow", "\320\241\320\272\320\260\321\201\321\203\320\262\320\260\321\202\320\270", nullptr));
        agreeButton->setText(QCoreApplication::translate("DisciplineProcessWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DisciplineProcessWindow: public Ui_DisciplineProcessWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISCIPLINEPROCESSWINDOW_H
