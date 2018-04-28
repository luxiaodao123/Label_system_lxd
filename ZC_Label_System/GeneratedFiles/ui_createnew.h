/********************************************************************************
** Form generated from reading UI file 'createnew.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATENEW_H
#define UI_CREATENEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateNew
{
public:
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QListWidget *listWidget;
    QLabel *label_2;

    void setupUi(QWidget *CreateNew)
    {
        if (CreateNew->objectName().isEmpty())
            CreateNew->setObjectName(QStringLiteral("CreateNew"));
        CreateNew->resize(399, 385);
        lineEdit = new QLineEdit(CreateNew);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(170, 50, 113, 20));
        label = new QLabel(CreateNew);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 50, 81, 20));
        pushButton = new QPushButton(CreateNew);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(90, 330, 75, 23));
        pushButton_2 = new QPushButton(CreateNew);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(200, 330, 75, 23));
        listWidget = new QListWidget(CreateNew);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(70, 80, 256, 241));
        label_2 = new QLabel(CreateNew);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(310, 50, 71, 16));

        retranslateUi(CreateNew);

        QMetaObject::connectSlotsByName(CreateNew);
    } // setupUi

    void retranslateUi(QWidget *CreateNew)
    {
        CreateNew->setWindowTitle(QApplication::translate("CreateNew", "Form", 0));
        label->setText(QApplication::translate("CreateNew", "\350\257\267\350\276\223\345\205\245\346\202\243\350\200\205ID:", 0));
        pushButton->setText(QApplication::translate("CreateNew", "\345\257\274\345\205\245\346\225\260\346\215\256", 0));
        pushButton_2->setText(QApplication::translate("CreateNew", "\347\241\256\345\256\232", 0));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CreateNew: public Ui_CreateNew {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATENEW_H
