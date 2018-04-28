/********************************************************************************
** Form generated from reading UI file 'mainaccountwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINACCOUNTWINDOW_H
#define UI_MAINACCOUNTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainAccountWindow
{
public:
    QPushButton *add;
    QPushButton *delete_2;
    QPushButton *modify;
    QTableWidget *tableWidget;
    QLabel *label;

    void setupUi(QWidget *MainAccountWindow)
    {
        if (MainAccountWindow->objectName().isEmpty())
            MainAccountWindow->setObjectName(QStringLiteral("MainAccountWindow"));
        MainAccountWindow->resize(558, 507);
        add = new QPushButton(MainAccountWindow);
        add->setObjectName(QStringLiteral("add"));
        add->setGeometry(QRect(60, 30, 61, 41));
        add->setStyleSheet(QStringLiteral(""));
        delete_2 = new QPushButton(MainAccountWindow);
        delete_2->setObjectName(QStringLiteral("delete_2"));
        delete_2->setGeometry(QRect(220, 30, 61, 41));
        modify = new QPushButton(MainAccountWindow);
        modify->setObjectName(QStringLiteral("modify"));
        modify->setGeometry(QRect(380, 30, 61, 41));
        tableWidget = new QTableWidget(MainAccountWindow);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(20, 80, 511, 351));
        label = new QLabel(MainAccountWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 81, 31));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        retranslateUi(MainAccountWindow);

        QMetaObject::connectSlotsByName(MainAccountWindow);
    } // setupUi

    void retranslateUi(QWidget *MainAccountWindow)
    {
        MainAccountWindow->setWindowTitle(QApplication::translate("MainAccountWindow", "Form", 0));
        add->setText(QApplication::translate("MainAccountWindow", "\346\267\273\345\212\240", 0));
        delete_2->setText(QApplication::translate("MainAccountWindow", "\345\210\240\351\231\244", 0));
        modify->setText(QApplication::translate("MainAccountWindow", "\344\277\256\346\224\271", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainAccountWindow", "\345\272\217\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainAccountWindow", "\345\247\223\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainAccountWindow", "\347\224\250\346\210\267\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainAccountWindow", "\345\257\206\347\240\201", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainAccountWindow", "\345\244\207\346\263\250", 0));
        label->setText(QApplication::translate("MainAccountWindow", "\350\264\246\346\210\267\347\256\241\347\220\206", 0));
    } // retranslateUi

};

namespace Ui {
    class MainAccountWindow: public Ui_MainAccountWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINACCOUNTWINDOW_H
