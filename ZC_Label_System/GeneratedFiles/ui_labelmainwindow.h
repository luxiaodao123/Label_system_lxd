/********************************************************************************
** Form generated from reading UI file 'labelmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABELMAINWINDOW_H
#define UI_LABELMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyLabel/paintlabel.h"

QT_BEGIN_NAMESPACE

class Ui_LabelMainWindow
{
public:
    QAction *AccountManagement;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_7;
    QAction *createnew;
    QAction *allsave;
    QAction *load;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *widget_3;
    QToolButton *edit;
    QToolButton *big;
    QToolButton *sma;
    QToolButton *save;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *last;
    QPushButton *next;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_6;
    QGridLayout *gridLayout_3;
    QListWidget *listWidget;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QTreeWidget *donot;
    QTreeWidget *already;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_2;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_3;
	QHBoxLayout *horizontalLayout_L1;
    QScrollArea *scrollArea;
	QScrollArea *scrollArea_L1;
    QWidget *scrollAreaWidgetContents_2;
	QWidget *scrollAreaWidgetContents_L2;
    QLabel *pixLabel;
    PaintLabel *paintLabel;
	PaintLabel *paintLabel_L3;
    QTreeWidget *focuslabel;
	QTreeWidget *focuslabel_1;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *oneEye;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_3;
	QFont font_1;

    void setupUi(QMainWindow *LabelMainWindow)
    {
        if (LabelMainWindow->objectName().isEmpty())
            LabelMainWindow->setObjectName(QStringLiteral("LabelMainWindow"));
        LabelMainWindow->resize(2560, 1440);
        AccountManagement = new QAction(LabelMainWindow);
        AccountManagement->setObjectName(QStringLiteral("AccountManagement"));
        action_2 = new QAction(LabelMainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_3 = new QAction(LabelMainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        action_4 = new QAction(LabelMainWindow);
        action_4->setObjectName(QStringLiteral("action_4"));
        action_5 = new QAction(LabelMainWindow);
        action_5->setObjectName(QStringLiteral("action_5"));
        action_7 = new QAction(LabelMainWindow);
        action_7->setObjectName(QStringLiteral("action_7"));
        createnew = new QAction(LabelMainWindow);
        createnew->setObjectName(QStringLiteral("createnew"));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei UI"));
        createnew->setFont(font);
        allsave = new QAction(LabelMainWindow);
        allsave->setObjectName(QStringLiteral("allsave"));
        load = new QAction(LabelMainWindow);
        load->setObjectName(QStringLiteral("load"));
        load->setFont(font);
        centralwidget = new QWidget(LabelMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(1);
        gridLayout->setContentsMargins(2, 2, 2, 2);
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMaximumSize(QSize(16777215, 30));
        edit = new QToolButton(widget_3);
        edit->setObjectName(QStringLiteral("edit"));
        edit->setGeometry(QRect(0, 0, 30, 30));
        edit->setStyleSheet(QLatin1String("  \n"
"QToolButton::item:clicked:active{  \n"
"    background: #5a8ae0;  \n"
"}  \n"
"\n"
""));
        big = new QToolButton(widget_3);
        big->setObjectName(QStringLiteral("big"));
        big->setGeometry(QRect(40, 0, 30, 30));
        big->setStyleSheet(QLatin1String("  \n"
"QToolButton::item:clicked:active{  \n"
"    background: #5a8ae0;  \n"
"}  \n"
"\n"
""));
        sma = new QToolButton(widget_3);
        sma->setObjectName(QStringLiteral("sma"));
        sma->setGeometry(QRect(80, 0, 30, 30));
        sma->setStyleSheet(QLatin1String("  \n"
"QToolButton::item:clicked:active{  \n"
"    background: #5a8ae0;  \n"
"}  \n"
"\n"
""));
        save = new QToolButton(widget_3);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(120, 0, 30, 30));
        save->setStyleSheet(QLatin1String("  \n"
"QToolButton::item:clicked:active{  \n"
"    background: #5a8ae0;  \n"
"}  \n"
"\n"
""));

        gridLayout->addWidget(widget_3, 1, 1, 1, 1);

        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMaximumSize(QSize(16777215, 140));
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        horizontalLayout_2 = new QHBoxLayout(widget_5);
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        label_6 = new QLabel(widget_5);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font1;
        font1.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font1.setPointSize(16);
        label_6->setFont(font1);

        horizontalLayout_2->addWidget(label_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        last = new QPushButton(widget_5);
        last->setObjectName(QStringLiteral("last"));
        last->setMaximumSize(QSize(100, 16777215));
        last->setFont(font1);
        last->setStyleSheet(QLatin1String("  \n"
"QPushButton::item:selected:active{  \n"
"    background: #5a8ae0;  \n"
"}  "));

        horizontalLayout_2->addWidget(last);

        next = new QPushButton(widget_5);
        next->setObjectName(QStringLiteral("next"));
        next->setMaximumSize(QSize(100, 16777215));
        next->setFont(font1);
        next->setStyleSheet(QLatin1String("  \n"
"QPushButton::item:clicked:active{  \n"
"    background: #5a8ae0;  \n"
"}  \n"
"  \n"
""));

        horizontalLayout_2->addWidget(next);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget_5);

        widget_6 = new QWidget(widget_4);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        gridLayout_3 = new QGridLayout(widget_6);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(widget_6);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout_3->addWidget(listWidget, 0, 0, 1, 1);


        verticalLayout->addWidget(widget_6);


        gridLayout->addWidget(widget_4, 4, 1, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 0));
        widget->setMaximumSize(QSize(256, 16777215));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(1);
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        donot = new QTreeWidget(widget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setFont(0, font1);
        donot->setHeaderItem(__qtreewidgetitem);
        donot->setObjectName(QStringLiteral("donot"));
        donot->setMinimumSize(QSize(125, 0));
        donot->setStyleSheet(QLatin1String("QTreeWidget{  \n"
"        background-color: #ffffff;  \n"
"      \n"
"        /* set the font properties*/  \n"
"        font-size:17px;  \n"
"        color: black;  \n"
"    } \n"
"\n"
"QTreeWidget::item:hover {  \n"
"    background: #d8dbdd;  \n"
"}  \n"
"  \n"
"QTreeWidget::item:selected:active{  \n"
"    background: #5a8ae0;  \n"
"}  \n"
"  \n"
"QTreeWidget::item:selected:!active {  \n"
"    /*background: rgb(63, 147, 168); */ \n"
"}"));

        gridLayout_2->addWidget(donot, 0, 0, 1, 1);

        already = new QTreeWidget(widget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setFont(0, font1);
        already->setHeaderItem(__qtreewidgetitem1);
        already->setObjectName(QStringLiteral("already"));
        already->setStyleSheet(QLatin1String("QTreeWidget{  \n"
"        background-color: #ffffff;  \n"
"      \n"
"        /* set the font properties*/  \n"
"        font-size:17px;  \n"
"        color: black;  \n"
"    } \n"
"\n"
"QTreeWidget::item:hover {  \n"
"    background: #d8dbdd;  \n"
"}  \n"
"  \n"
"QTreeWidget::item:selected:active{  \n"
"    background: #5a8ae0;  \n"
"}  \n"
"  \n"
"QTreeWidget::item:selected:!active {  \n"
"    /*background: rgb(63, 147, 168); */ \n"
"}"));

        gridLayout_2->addWidget(already, 1, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 5, 1);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMaximumSize(QSize(16777215, 40));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(90, 16777215));
        QFont font2;
        font2.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font2.setPointSize(14);
        label->setFont(font2);

        horizontalLayout->addWidget(label);

        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(30, 16777215));
        label_7->setFont(font2);

        horizontalLayout->addWidget(label_7);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(90, 16777215));
        label_2->setFont(font2);

        horizontalLayout->addWidget(label_2);

        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(0, 0));
        label_5->setMaximumSize(QSize(250, 16777215));
        label_5->setFont(font2);

        horizontalLayout->addWidget(label_5);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(80, 16777215));
        label_4->setFont(font2);

        horizontalLayout->addWidget(label_4);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(false);
        label_3->setMinimumSize(QSize(0, 0));
        label_3->setFont(font2);

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout->addWidget(widget_2, 0, 1, 1, 3);

        widget_8 = new QWidget(centralwidget);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        horizontalLayout_3 = new QHBoxLayout(widget_8);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        scrollArea = new QScrollArea(widget_8);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setMinimumSize(QSize(0, 0));
        scrollArea->setStyleSheet(QLatin1String("QScrollArea{  \n"
"        background-color: #ffffff;  \n"
"} "));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 1772, 1165));
        pixLabel = new QLabel(scrollAreaWidgetContents_2);
        pixLabel->setObjectName(QStringLiteral("pixLabel"));
        pixLabel->setGeometry(QRect(0, 0, 1000, 666));
        paintLabel = new PaintLabel(scrollAreaWidgetContents_2);
        paintLabel->setObjectName(QStringLiteral("paintLabel"));
        paintLabel->setGeometry(QRect(0, 0, 1000, 666));
        paintLabel->setStyleSheet(QLatin1String("QScrollArea{  \n"
"        background-color: #ffffff;  \n"
"} \n"
""));
        scrollArea->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout_3->addWidget(scrollArea);

        focuslabel = new QTreeWidget(widget_8);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem();
        __qtreewidgetitem2->setFont(0, font1);
        focuslabel->setHeaderItem(__qtreewidgetitem2);
        focuslabel->setObjectName(QStringLiteral("focuslabel"));
        focuslabel->setMinimumSize(QSize(250, 0));
        focuslabel->setMaximumSize(QSize(200, 16777215));
        focuslabel->setStyleSheet(QLatin1String("    QTreeWidget{  \n"
"	   font: 75 14pt \"Microsoft JhengHei UI\";\n"
"        background-color: #ffffff;  \n"
"      \n"
"        /* set the font properties*/  \n"
"        /*font-size:17px;  */\n"
"        color: black;\n"
"    } \n"
"\n"
"QTreeWidget::item:hover {  \n"
"    background: #d8dbdd;  \n"
"}  \n"
"  \n"
"QTreeWidget::item:selected:active{  \n"
"   /* background: #5a8ae0;  */\n"
"}  \n"
"  \n"
"QTreeWidget::item::true {  \n"
"    /*background: rgb(63, 147, 168); */ 	\n"
"}"));

        horizontalLayout_3->addWidget(focuslabel);


        gridLayout->addWidget(widget_8, 2, 1, 2, 2);

        widget_7 = new QWidget(centralwidget);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setMinimumSize(QSize(250, 0));
        widget_7->setMaximumSize(QSize(250, 16777215));
        verticalLayout_2 = new QVBoxLayout(widget_7);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        oneEye = new QTreeWidget(widget_7);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem();
        __qtreewidgetitem3->setFont(0, font1);
        oneEye->setHeaderItem(__qtreewidgetitem3);
        oneEye->setObjectName(QStringLiteral("oneEye"));
        oneEye->setMinimumSize(QSize(250, 0));
        oneEye->setMaximumSize(QSize(250, 16777215));
        oneEye->setStyleSheet(QLatin1String("    QTreeWidget{  \n"
"        background-color: #ffffff;  \n"
"        font: 75 14pt \"Microsoft JhengHei UI\";\n"
"        /* set the font properties*/  \n"
"        /*font-size:17px;  */\n"
"        color: black;  \n"
"    } \n"
"\n"
"QTreeWidget::item:hover {  \n"
"    background: #d8dbdd;  \n"
"}  \n"
"  \n"
"QTreeWidget::item:selected:active{  \n"
"   /* background: #5a8ae0;  */\n"
"}  \n"
"  \n"
"QTreeWidget::item:selected:!active {  \n"
"    /*background: rgb(63, 147, 168); */ \n"
"}"));
        oneEye->setSortingEnabled(false);

        verticalLayout_2->addWidget(oneEye);


        gridLayout->addWidget(widget_7, 2, 3, 3, 1);

        LabelMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LabelMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 2560, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        LabelMainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(createnew);
        menu->addAction(load);

        retranslateUi(LabelMainWindow);

        QMetaObject::connectSlotsByName(LabelMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LabelMainWindow)
    {
        LabelMainWindow->setWindowTitle(QApplication::translate("LabelMainWindow", "\346\231\272\346\210\220\346\240\207\346\263\250\350\275\257\344\273\266", 0));
        AccountManagement->setText(QApplication::translate("LabelMainWindow", "\350\264\246\346\210\267\347\256\241\347\220\206", 0));
        action_2->setText(QApplication::translate("LabelMainWindow", "\346\235\203\351\231\220\347\256\241\347\220\206", 0));
        action_3->setText(QApplication::translate("LabelMainWindow", "\347\273\237\350\256\241\345\210\206\346\236\220", 0));
        action_4->setText(QApplication::translate("LabelMainWindow", "\347\273\223\346\236\234\345\257\274\345\207\272", 0));
        action_5->setText(QApplication::translate("LabelMainWindow", "\346\227\245\345\277\227\347\256\241\347\220\206", 0));
        action_7->setText(QApplication::translate("LabelMainWindow", "\345\267\245\344\275\234\346\250\241\345\274\217", 0));
        createnew->setText(QApplication::translate("LabelMainWindow", "\346\226\260\345\273\272", 0));
        allsave->setText(QApplication::translate("LabelMainWindow", "\344\277\235\345\255\230", 0));
        load->setText(QApplication::translate("LabelMainWindow", "\345\257\274\345\205\245", 0));
        edit->setText(QApplication::translate("LabelMainWindow", "...", 0));
        big->setText(QApplication::translate("LabelMainWindow", "...", 0));
        sma->setText(QApplication::translate("LabelMainWindow", "...", 0));
        save->setText(QApplication::translate("LabelMainWindow", "...", 0));
        label_6->setText(QApplication::translate("LabelMainWindow", "\345\233\276\345\203\217", 0));
        last->setText(QApplication::translate("LabelMainWindow", "<\344\270\212\344\270\200\345\274\240", 0));
        next->setText(QApplication::translate("LabelMainWindow", "\344\270\213\344\270\200\345\274\240>", 0));
        QTreeWidgetItem *___qtreewidgetitem = donot->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("LabelMainWindow", "\346\234\252\346\240\207\346\263\250", 0));
        QTreeWidgetItem *___qtreewidgetitem1 = already->headerItem();
        ___qtreewidgetitem1->setText(0, QApplication::translate("LabelMainWindow", "\345\267\262\346\240\207\346\263\250", 0));
        label->setText(QApplication::translate("LabelMainWindow", "\346\226\207\344\273\266\346\200\273\346\225\260\357\274\232", 0));
        label_7->setText(QString());
        label_2->setText(QApplication::translate("LabelMainWindow", "\346\226\207\344\273\266\345\244\271\345\220\215\357\274\232", 0));
        label_5->setText(QString());
        label_4->setText(QApplication::translate("LabelMainWindow", "\346\226\207\344\273\266\345\220\215\357\274\232", 0));
        label_3->setText(QString());
        pixLabel->setText(QString());
        paintLabel->setText(QString());
        QTreeWidgetItem *___qtreewidgetitem2 = focuslabel->headerItem();
        ___qtreewidgetitem2->setText(0, QApplication::translate("LabelMainWindow", "\346\240\207\350\256\260\345\214\272\345\237\237", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = oneEye->headerItem();
        ___qtreewidgetitem3->setText(0, QApplication::translate("LabelMainWindow", "\345\215\225\345\274\240\345\233\276\347\211\207\350\257\204\347\272\247", 0));
        menu->setTitle(QApplication::translate("LabelMainWindow", "\347\274\226\350\276\221", 0));
        menu_3->setTitle(QApplication::translate("LabelMainWindow", "\345\270\256\345\212\251", 0));
    } // retranslateUi

};

namespace Ui {
    class LabelMainWindow: public Ui_LabelMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABELMAINWINDOW_H
