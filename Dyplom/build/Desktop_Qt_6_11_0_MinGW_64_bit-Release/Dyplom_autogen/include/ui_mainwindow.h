/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *Header;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *configYearComboBox;
    QPushButton *addNewYearButton;
    QPushButton *exportButton;
    QPushButton *importButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *undoButton;
    QTabWidget *tabWidget;
    QWidget *tabTeacherLayout;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QLineEdit *searchTeacherLineEdit;
    QToolButton *searchTeacherButton;
    QTableView *teacherTableView;
    QWidget *tabLeson;
    QVBoxLayout *verticalLayout_8;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget_5;
    QLineEdit *searchDisciplineLineEdit;
    QToolButton *searchDisciplineButton;
    QTableView *disciplineTableView;
    QWidget *tabGroup;
    QVBoxLayout *verticalLayout_10;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_9;
    QWidget *widget_6;
    QLineEdit *searchGroupSpecialityLineEdit;
    QToolButton *searchGroupOrDepartmentButton;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_10;
    QTableView *groupTabelView;
    QTableView *specialityTableView;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_5;
    QStackedWidget *footerStack;
    QWidget *footerTeacherLoad;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addTeacherButton;
    QWidget *footerLeson;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *addDisciplineButton;
    QWidget *footerGroup;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *addGroupButton;
    QPushButton *addSpecialityButton;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *deleatButton;
    QSpacerItem *horizontalSpacer_10;
    QFrame *settingFrame;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *setteningButton;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1692, 694);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Header = new QFrame(centralwidget);
        Header->setObjectName("Header");
        Header->setMinimumSize(QSize(0, 92));
        Header->setStyleSheet(QString::fromUtf8("background-color: rgb(237, 237, 237);\n"
"border: 1px solid rgb(139, 139, 139);\n"
"\n"
"\n"
""));
        Header->setFrameShape(QFrame::Shape::StyledPanel);
        Header->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_4 = new QHBoxLayout(Header);
        horizontalLayout_4->setSpacing(26);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(24);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        widget_2 = new QWidget(Header);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(10, 0));
        widget_2->setStyleSheet(QString::fromUtf8("border: 0px;"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(34, -1, -1, -1);
        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 16px;"));

        horizontalLayout->addWidget(label);

        configYearComboBox = new QComboBox(widget_2);
        configYearComboBox->setObjectName("configYearComboBox");
        configYearComboBox->setMinimumSize(QSize(124, 34));
        configYearComboBox->setSizeIncrement(QSize(0, 0));
        configYearComboBox->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font-size: 16px;\n"
"border: 1px solid rgb(120, 120, 120);\n"
"border-radius: 2px;"));

        horizontalLayout->addWidget(configYearComboBox);


        horizontalLayout_3->addWidget(widget_2);

        addNewYearButton = new QPushButton(Header);
        addNewYearButton->setObjectName("addNewYearButton");
        addNewYearButton->setMinimumSize(QSize(0, 34));
        addNewYearButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"\n"
""));

        horizontalLayout_3->addWidget(addNewYearButton);

        exportButton = new QPushButton(Header);
        exportButton->setObjectName("exportButton");
        exportButton->setMinimumSize(QSize(0, 34));
        exportButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        exportButton->setAutoDefault(false);
        exportButton->setFlat(false);

        horizontalLayout_3->addWidget(exportButton);

        importButton = new QPushButton(Header);
        importButton->setObjectName("importButton");
        importButton->setMinimumSize(QSize(0, 34));
        importButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        horizontalLayout_3->addWidget(importButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        undoButton = new QPushButton(Header);
        undoButton->setObjectName("undoButton");
        undoButton->setMinimumSize(QSize(0, 34));
        undoButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"\n"
""));

        horizontalLayout_3->addWidget(undoButton);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(Header);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        tabTeacherLayout = new QWidget();
        tabTeacherLayout->setObjectName("tabTeacherLayout");
        verticalLayout_2 = new QVBoxLayout(tabTeacherLayout);
        verticalLayout_2->setSpacing(26);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(10, 10, 10, 0);
        frame_2 = new QFrame(tabTeacherLayout);
        frame_2->setObjectName("frame_2");
        frame_2->setMinimumSize(QSize(0, 82));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(233, 233, 233);"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(54, -1, -1, -1);
        widget = new QWidget(frame_2);
        widget->setObjectName("widget");
        searchTeacherLineEdit = new QLineEdit(widget);
        searchTeacherLineEdit->setObjectName("searchTeacherLineEdit");
        searchTeacherLineEdit->setGeometry(QRect(0, 20, 186, 24));
        searchTeacherLineEdit->setMinimumSize(QSize(0, 24));
        searchTeacherLineEdit->setMaximumSize(QSize(186, 16777215));
        searchTeacherLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        searchTeacherButton = new QToolButton(widget);
        searchTeacherButton->setObjectName("searchTeacherButton");
        searchTeacherButton->setGeometry(QRect(180, 20, 24, 24));
        searchTeacherButton->setMinimumSize(QSize(24, 24));
        searchTeacherButton->setMaximumSize(QSize(24, 24));
        searchTeacherButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid #8f8f91;"));

        verticalLayout_3->addWidget(widget);


        verticalLayout_2->addWidget(frame_2);

        teacherTableView = new QTableView(tabTeacherLayout);
        teacherTableView->setObjectName("teacherTableView");

        verticalLayout_2->addWidget(teacherTableView);

        tabWidget->addTab(tabTeacherLayout, QString());
        tabLeson = new QWidget();
        tabLeson->setObjectName("tabLeson");
        verticalLayout_8 = new QVBoxLayout(tabLeson);
        verticalLayout_8->setSpacing(26);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(10, 10, 10, 0);
        frame_4 = new QFrame(tabLeson);
        frame_4->setObjectName("frame_4");
        frame_4->setMinimumSize(QSize(0, 82));
        frame_4->setStyleSheet(QString::fromUtf8("background-color: rgb(233, 233, 233);"));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_4);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(54, -1, -1, -1);
        widget_5 = new QWidget(frame_4);
        widget_5->setObjectName("widget_5");
        searchDisciplineLineEdit = new QLineEdit(widget_5);
        searchDisciplineLineEdit->setObjectName("searchDisciplineLineEdit");
        searchDisciplineLineEdit->setGeometry(QRect(0, 20, 186, 24));
        searchDisciplineLineEdit->setMinimumSize(QSize(0, 24));
        searchDisciplineLineEdit->setMaximumSize(QSize(186, 16777215));
        searchDisciplineLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        searchDisciplineButton = new QToolButton(widget_5);
        searchDisciplineButton->setObjectName("searchDisciplineButton");
        searchDisciplineButton->setGeometry(QRect(180, 20, 24, 24));
        searchDisciplineButton->setMinimumSize(QSize(24, 24));
        searchDisciplineButton->setMaximumSize(QSize(24, 24));
        searchDisciplineButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid #8f8f91;"));

        verticalLayout_7->addWidget(widget_5);


        verticalLayout_8->addWidget(frame_4);

        disciplineTableView = new QTableView(tabLeson);
        disciplineTableView->setObjectName("disciplineTableView");

        verticalLayout_8->addWidget(disciplineTableView);

        tabWidget->addTab(tabLeson, QString());
        tabGroup = new QWidget();
        tabGroup->setObjectName("tabGroup");
        verticalLayout_10 = new QVBoxLayout(tabGroup);
        verticalLayout_10->setSpacing(26);
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_10->setContentsMargins(10, 10, 10, 0);
        frame_5 = new QFrame(tabGroup);
        frame_5->setObjectName("frame_5");
        frame_5->setMinimumSize(QSize(0, 82));
        frame_5->setStyleSheet(QString::fromUtf8("background-color: rgb(233, 233, 233);"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_9 = new QVBoxLayout(frame_5);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(54, -1, -1, -1);
        widget_6 = new QWidget(frame_5);
        widget_6->setObjectName("widget_6");
        searchGroupSpecialityLineEdit = new QLineEdit(widget_6);
        searchGroupSpecialityLineEdit->setObjectName("searchGroupSpecialityLineEdit");
        searchGroupSpecialityLineEdit->setGeometry(QRect(0, 20, 186, 24));
        searchGroupSpecialityLineEdit->setMinimumSize(QSize(0, 24));
        searchGroupSpecialityLineEdit->setMaximumSize(QSize(186, 16777215));
        searchGroupSpecialityLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        searchGroupOrDepartmentButton = new QToolButton(widget_6);
        searchGroupOrDepartmentButton->setObjectName("searchGroupOrDepartmentButton");
        searchGroupOrDepartmentButton->setGeometry(QRect(180, 20, 24, 24));
        searchGroupOrDepartmentButton->setMinimumSize(QSize(24, 24));
        searchGroupOrDepartmentButton->setMaximumSize(QSize(24, 24));
        searchGroupOrDepartmentButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 1px solid #8f8f91;"));

        verticalLayout_9->addWidget(widget_6);


        verticalLayout_10->addWidget(frame_5);

        frame_3 = new QFrame(tabGroup);
        frame_3->setObjectName("frame_3");
        frame_3->setStyleSheet(QString::fromUtf8("border: 0px;"));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_10 = new QHBoxLayout(frame_3);
        horizontalLayout_10->setSpacing(24);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        groupTabelView = new QTableView(frame_3);
        groupTabelView->setObjectName("groupTabelView");
        groupTabelView->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(115, 115, 115);"));

        horizontalLayout_10->addWidget(groupTabelView);

        specialityTableView = new QTableView(frame_3);
        specialityTableView->setObjectName("specialityTableView");
        specialityTableView->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(115, 115, 115);"));

        horizontalLayout_10->addWidget(specialityTableView);


        verticalLayout_10->addWidget(frame_3);

        tabWidget->addTab(tabGroup, QString());

        verticalLayout->addWidget(tabWidget);

        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMaximumSize(QSize(16777215, 62));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(237, 237, 237);\n"
"border-color: rgb(139, 139, 139);"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout_5->setContentsMargins(-1, 4, -1, 6);
        footerStack = new QStackedWidget(frame);
        footerStack->setObjectName("footerStack");
        footerStack->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(footerStack->sizePolicy().hasHeightForWidth());
        footerStack->setSizePolicy(sizePolicy1);
        footerStack->setMaximumSize(QSize(16777215, 62));
        footerStack->setStyleSheet(QString::fromUtf8(""));
        footerStack->setLocale(QLocale(QLocale::Russian, QLocale::Russia));
        footerTeacherLoad = new QWidget();
        footerTeacherLoad->setObjectName("footerTeacherLoad");
        sizePolicy1.setHeightForWidth(footerTeacherLoad->sizePolicy().hasHeightForWidth());
        footerTeacherLoad->setSizePolicy(sizePolicy1);
        footerTeacherLoad->setMinimumSize(QSize(15, 0));
        horizontalLayout_2 = new QHBoxLayout(footerTeacherLoad);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        addTeacherButton = new QPushButton(footerTeacherLoad);
        addTeacherButton->setObjectName("addTeacherButton");
        addTeacherButton->setMinimumSize(QSize(0, 34));
        addTeacherButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));

        horizontalLayout_2->addWidget(addTeacherButton);

        footerStack->addWidget(footerTeacherLoad);
        footerLeson = new QWidget();
        footerLeson->setObjectName("footerLeson");
        sizePolicy1.setHeightForWidth(footerLeson->sizePolicy().hasHeightForWidth());
        footerLeson->setSizePolicy(sizePolicy1);
        horizontalLayout_6 = new QHBoxLayout(footerLeson);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        addDisciplineButton = new QPushButton(footerLeson);
        addDisciplineButton->setObjectName("addDisciplineButton");
        addDisciplineButton->setMinimumSize(QSize(0, 34));
        addDisciplineButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));

        horizontalLayout_6->addWidget(addDisciplineButton);

        footerStack->addWidget(footerLeson);
        footerGroup = new QWidget();
        footerGroup->setObjectName("footerGroup");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(footerGroup->sizePolicy().hasHeightForWidth());
        footerGroup->setSizePolicy(sizePolicy2);
        horizontalLayout_8 = new QHBoxLayout(footerGroup);
        horizontalLayout_8->setSpacing(28);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        addGroupButton = new QPushButton(footerGroup);
        addGroupButton->setObjectName("addGroupButton");
        addGroupButton->setMinimumSize(QSize(0, 34));
        addGroupButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        horizontalLayout_8->addWidget(addGroupButton);

        addSpecialityButton = new QPushButton(footerGroup);
        addSpecialityButton->setObjectName("addSpecialityButton");
        addSpecialityButton->setMinimumSize(QSize(0, 34));
        addSpecialityButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        horizontalLayout_8->addWidget(addSpecialityButton);

        footerStack->addWidget(footerGroup);

        horizontalLayout_5->addWidget(footerStack);

        frame_6 = new QFrame(frame);
        frame_6->setObjectName("frame_6");
        frame_6->setMaximumSize(QSize(186, 16777215));
        frame_6->setStyleSheet(QString::fromUtf8("border-radius: 1px;"));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_9 = new QHBoxLayout(frame_6);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        deleatButton = new QPushButton(frame_6);
        deleatButton->setObjectName("deleatButton");
        deleatButton->setMinimumSize(QSize(0, 34));
        deleatButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        horizontalLayout_9->addWidget(deleatButton);


        horizontalLayout_5->addWidget(frame_6);

        horizontalSpacer_10 = new QSpacerItem(160, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        settingFrame = new QFrame(frame);
        settingFrame->setObjectName("settingFrame");
        settingFrame->setStyleSheet(QString::fromUtf8("border-radius: 1px;"));
        settingFrame->setFrameShape(QFrame::Shape::StyledPanel);
        settingFrame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_7 = new QHBoxLayout(settingFrame);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        setteningButton = new QPushButton(settingFrame);
        setteningButton->setObjectName("setteningButton");
        setteningButton->setMinimumSize(QSize(126, 34));
        setteningButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));

        horizontalLayout_7->addWidget(setteningButton);


        horizontalLayout_5->addWidget(settingFrame);

        horizontalLayout_5->setStretch(2, 1);

        verticalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1692, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        exportButton->setDefault(false);
        tabWidget->setCurrentIndex(1);
        footerStack->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\262\321\207\320\260\320\273\321\214\320\275\320\270\320\271 \321\200\321\226\320\272:", nullptr));
        addNewYearButton->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\262\320\276\321\200\320\270\321\202\320\270 \320\275\320\276\320\262\320\270\320\271 \321\200\321\226\320\272", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "\320\225\320\272\321\201\320\277\320\276\321\200\321\202 \320\262 Exel", nullptr));
        importButton->setText(QCoreApplication::translate("MainWindow", "\320\206\320\274\320\277\320\276\321\200\321\202 \320\267 \321\204\320\260\320\271\320\273\321\203", nullptr));
        undoButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\226\320\264\320\274\321\226\320\275\320\270\321\202\320\270", nullptr));
        searchTeacherLineEdit->setText(QString());
        searchTeacherButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabTeacherLayout), QCoreApplication::translate("MainWindow", "\320\235\320\260\320\262\320\260\320\275\321\202\320\260\320\266\320\265\320\275\320\275\321\217 \320\262\320\270\320\272\320\273\320\260\320\264\320\260\321\207\321\226\320\262", nullptr));
        searchDisciplineLineEdit->setText(QString());
        searchDisciplineButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabLeson), QCoreApplication::translate("MainWindow", "\320\224\320\270\321\201\321\206\320\270\320\277\320\273\321\226\320\275\320\270", nullptr));
        searchGroupSpecialityLineEdit->setText(QString());
        searchGroupOrDepartmentButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabGroup), QCoreApplication::translate("MainWindow", "\320\235\320\260\320\262\321\207\320\260\320\273\321\214\320\275\321\226 \320\263\321\200\321\203\320\277\320\270", nullptr));
        addTeacherButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\264\320\260\321\202\320\270 \320\262\320\270\320\272\320\273\320\260\320\264\320\260\321\207\320\260", nullptr));
        addDisciplineButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\264\320\260\321\202\320\270 \320\264\320\270\321\201\321\206\320\270\320\277\320\273\321\226\320\275\321\203", nullptr));
        addGroupButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\264\320\260\321\202\320\270 \320\263\321\200\321\203\320\277\321\203", nullptr));
        addSpecialityButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\264\320\260\321\202\320\270 \321\201\320\277\320\265\321\206\321\226\320\260\320\273\321\214\320\275\321\226\321\201\321\202\321\214", nullptr));
        deleatButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\264\320\260\320\273\320\265\320\275\320\275\321\217", nullptr));
        setteningButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\321\202\320\260\320\273\321\226 \320\275\320\260\320\262\320\260\320\275\321\202\320\260\320\266\320\265\320\275\320\275\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
