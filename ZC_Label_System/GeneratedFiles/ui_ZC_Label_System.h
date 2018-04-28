/********************************************************************************
** Form generated from reading UI file 'ZC_Label_System.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZC_LABEL_SYSTEM_H
#define UI_ZC_LABEL_SYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ZC_Label_SystemClass
{
public:
    QWidget *centralWidget;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *usr;
    QLabel *label;
    QPushButton *reset;
    QPushButton *login;
    QLineEdit *pwd;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ZC_Label_SystemClass)
    {
        if (ZC_Label_SystemClass->objectName().isEmpty())
            ZC_Label_SystemClass->setObjectName(QStringLiteral("ZC_Label_SystemClass"));
        ZC_Label_SystemClass->resize(295, 247);
        centralWidget = new QWidget(ZC_Label_SystemClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 60, 54, 12));
        QFont font;
        font.setPointSize(10);
        label_2->setFont(font);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 90, 54, 12));
        label_3->setFont(font);
        usr = new QLineEdit(centralWidget);
        usr->setObjectName(QStringLiteral("usr"));
        usr->setGeometry(QRect(120, 60, 113, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 111, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        reset = new QPushButton(centralWidget);
        reset->setObjectName(QStringLiteral("reset"));
        reset->setGeometry(QRect(170, 130, 75, 23));
        login = new QPushButton(centralWidget);
        login->setObjectName(QStringLiteral("login"));
        login->setGeometry(QRect(60, 130, 75, 23));
        pwd = new QLineEdit(centralWidget);
        pwd->setObjectName(QStringLiteral("pwd"));
        pwd->setGeometry(QRect(120, 90, 113, 20));
        ZC_Label_SystemClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ZC_Label_SystemClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 295, 23));
        ZC_Label_SystemClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ZC_Label_SystemClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ZC_Label_SystemClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ZC_Label_SystemClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ZC_Label_SystemClass->setStatusBar(statusBar);
        QWidget::setTabOrder(usr, pwd);
        QWidget::setTabOrder(pwd, login);
        QWidget::setTabOrder(login, reset);

        retranslateUi(ZC_Label_SystemClass);

        QMetaObject::connectSlotsByName(ZC_Label_SystemClass);
    } // setupUi

    void retranslateUi(QMainWindow *ZC_Label_SystemClass)
    {
        ZC_Label_SystemClass->setWindowTitle(QApplication::translate("ZC_Label_SystemClass", "ZC_Label_System", 0));
        label_2->setText(QApplication::translate("ZC_Label_SystemClass", "\347\224\250\346\210\267\345\220\215", 0));
        label_3->setText(QApplication::translate("ZC_Label_SystemClass", "\345\257\206\347\240\201", 0));
        label->setText(QApplication::translate("ZC_Label_SystemClass", "\347\224\250\346\210\267\347\231\273\345\275\225", 0));
        reset->setText(QApplication::translate("ZC_Label_SystemClass", "\351\207\215\347\275\256", 0));
        login->setText(QApplication::translate("ZC_Label_SystemClass", "\347\231\273\345\275\225", 0));
        login->setShortcut(QApplication::translate("ZC_Label_SystemClass", "Return", 0));
    } // retranslateUi

};

namespace Ui {
    class ZC_Label_SystemClass: public Ui_ZC_Label_SystemClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZC_LABEL_SYSTEM_H
