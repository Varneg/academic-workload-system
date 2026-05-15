/********************************************************************************
** Form generated from reading UI file 'importwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTWINDOW_H
#define UI_IMPORTWINDOW_H

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

QT_BEGIN_NAMESPACE

class Ui_ImportWindow
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *departmentLineEdit;
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

    void setupUi(QDialog *ImportWindow)
    {
        if (ImportWindow->objectName().isEmpty())
            ImportWindow->setObjectName("ImportWindow");
        ImportWindow->resize(360, 193);
        verticalLayout = new QVBoxLayout(ImportWindow);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame_3 = new QFrame(ImportWindow);
        frame_3->setObjectName("frame_3");
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(frame_3);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        departmentLineEdit = new QLineEdit(frame_3);
        departmentLineEdit->setObjectName("departmentLineEdit");

        horizontalLayout->addWidget(departmentLineEdit);


        verticalLayout->addWidget(frame_3);

        frame = new QFrame(ImportWindow);
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

        frame_2 = new QFrame(ImportWindow);
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


        retranslateUi(ImportWindow);

        QMetaObject::connectSlotsByName(ImportWindow);
    } // setupUi

    void retranslateUi(QDialog *ImportWindow)
    {
        ImportWindow->setWindowTitle(QCoreApplication::translate("ImportWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ImportWindow", "\320\222\320\262\320\265\320\264\321\226\321\202\321\214 \320\272\320\260\321\204\320\265\320\264\321\200\321\203", nullptr));
        label_2->setText(QCoreApplication::translate("ImportWindow", "\320\236\320\261\320\265\321\200\321\226\321\202\321\214\320\261 \321\204\320\260\320\271\320\273  ", nullptr));
        chooseFilePushButton->setText(QCoreApplication::translate("ImportWindow", "\320\236\320\261\321\200\320\260\321\202\320\270 \321\204\320\260\320\271\320\273", nullptr));
        cancelButon->setText(QCoreApplication::translate("ImportWindow", "\320\241\320\272\320\260\321\201\321\203\320\262\320\260\321\202\320\270", nullptr));
        agreeButton->setText(QCoreApplication::translate("ImportWindow", "\320\206\320\274\320\277\320\276\321\200\321\202\321\203\320\262\320\260\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImportWindow: public Ui_ImportWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTWINDOW_H
