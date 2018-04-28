/********************************************************************************
** Form generated from reading UI file 'add.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_H
#define UI_ADD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Add
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLabel *label_6;
    QLineEdit *lineEdit_5;

    void setupUi(QWidget *Add)
    {
        if (Add->objectName().isEmpty())
            Add->setObjectName(QStringLiteral("Add"));
        Add->resize(353, 424);
        label = new QLabel(Add);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 151, 41));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(Add);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 60, 54, 25));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        lineEdit = new QLineEdit(Add);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(100, 60, 200, 25));
        pushButton = new QPushButton(Add);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(90, 270, 61, 31));
        pushButton_2 = new QPushButton(Add);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(180, 270, 61, 31));
        label_3 = new QLabel(Add);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 100, 54, 25));
        label_3->setFont(font1);
        lineEdit_2 = new QLineEdit(Add);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(100, 100, 200, 25));
        label_4 = new QLabel(Add);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 140, 54, 25));
        label_4->setFont(font1);
        lineEdit_3 = new QLineEdit(Add);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(100, 140, 200, 25));
        label_5 = new QLabel(Add);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 180, 71, 25));
        label_5->setFont(font1);
        lineEdit_4 = new QLineEdit(Add);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(100, 180, 200, 25));
        label_6 = new QLabel(Add);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 220, 54, 25));
        label_6->setFont(font1);
        lineEdit_5 = new QLineEdit(Add);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(100, 220, 200, 25));

        retranslateUi(Add);

        QMetaObject::connectSlotsByName(Add);
    } // setupUi

    void retranslateUi(QWidget *Add)
    {
        Add->setWindowTitle(QApplication::translate("Add", "Form", 0));
        label->setText(QApplication::translate("Add", "\346\267\273\345\212\240\347\224\250\346\210\267", 0));
        label_2->setText(QApplication::translate("Add", "\345\247\223\345\220\215", 0));
        pushButton->setText(QApplication::translate("Add", "\347\241\256\350\256\244", 0));
        pushButton_2->setText(QApplication::translate("Add", "\345\217\226\346\266\210", 0));
        label_3->setText(QApplication::translate("Add", "\347\224\250\346\210\267\345\220\215", 0));
        label_4->setText(QApplication::translate("Add", "\345\257\206\347\240\201", 0));
        label_5->setText(QApplication::translate("Add", "\347\241\256\350\256\244\345\257\206\347\240\201", 0));
        label_6->setText(QApplication::translate("Add", "\345\247\223\345\220\215", 0));
    } // retranslateUi

};

namespace Ui {
    class Add: public Ui_Add {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_H
