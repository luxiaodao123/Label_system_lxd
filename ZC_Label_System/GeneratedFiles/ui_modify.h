/********************************************************************************
** Form generated from reading UI file 'modify.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFY_H
#define UI_MODIFY_H

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

class Ui_Modify
{
public:
    QLabel *label_6;
    QPushButton *pushButton_3;
    QLabel *label_3;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Modify)
    {
        if (Modify->objectName().isEmpty())
            Modify->setObjectName(QStringLiteral("Modify"));
        Modify->resize(346, 361);
        label_6 = new QLabel(Modify);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 210, 54, 25));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_6->setFont(font);
        pushButton_3 = new QPushButton(Modify);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(240, 260, 61, 31));
        label_3 = new QLabel(Modify);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 90, 54, 25));
        label_3->setFont(font);
        lineEdit_5 = new QLineEdit(Modify);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(100, 210, 200, 25));
        lineEdit_2 = new QLineEdit(Modify);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(100, 90, 200, 25));
        pushButton = new QPushButton(Modify);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 260, 61, 31));
        lineEdit = new QLineEdit(Modify);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(100, 50, 200, 25));
        label_4 = new QLabel(Modify);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 130, 54, 25));
        label_4->setFont(font);
        lineEdit_3 = new QLineEdit(Modify);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(100, 130, 200, 25));
        label_5 = new QLabel(Modify);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 170, 71, 25));
        label_5->setFont(font);
        lineEdit_4 = new QLineEdit(Modify);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(100, 170, 200, 25));
        label = new QLabel(Modify);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 151, 41));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label_2 = new QLabel(Modify);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 50, 54, 25));
        label_2->setFont(font);
        pushButton_2 = new QPushButton(Modify);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 260, 61, 31));

        retranslateUi(Modify);

        QMetaObject::connectSlotsByName(Modify);
    } // setupUi

    void retranslateUi(QWidget *Modify)
    {
        Modify->setWindowTitle(QApplication::translate("Modify", "Form", 0));
        label_6->setText(QApplication::translate("Modify", "\345\247\223\345\220\215", 0));
        pushButton_3->setText(QApplication::translate("Modify", "\351\207\215\347\275\256", 0));
        label_3->setText(QApplication::translate("Modify", "\347\224\250\346\210\267\345\220\215", 0));
        pushButton->setText(QApplication::translate("Modify", "\347\241\256\350\256\244", 0));
        label_4->setText(QApplication::translate("Modify", "\345\257\206\347\240\201", 0));
        label_5->setText(QApplication::translate("Modify", "\347\241\256\350\256\244\345\257\206\347\240\201", 0));
        label->setText(QApplication::translate("Modify", "\344\277\256\346\224\271\347\224\250\346\210\267\344\277\241\346\201\257", 0));
        label_2->setText(QApplication::translate("Modify", "\345\247\223\345\220\215", 0));
        pushButton_2->setText(QApplication::translate("Modify", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class Modify: public Ui_Modify {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFY_H
