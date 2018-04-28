/********************************************************************************
** Form generated from reading UI file 'process.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESS_H
#define UI_PROCESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Process
{
public:
    QProgressBar *progressBar;
    QLabel *label;

    void setupUi(QWidget *Process)
    {
        if (Process->objectName().isEmpty())
            Process->setObjectName(QStringLiteral("Process"));
        Process->resize(403, 217);
        progressBar = new QProgressBar(Process);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(50, 100, 301, 31));
        progressBar->setMaximum(9999999);
        progressBar->setValue(0);
        label = new QLabel(Process);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 62, 54, 20));

        retranslateUi(Process);

        QMetaObject::connectSlotsByName(Process);
    } // setupUi

    void retranslateUi(QWidget *Process)
    {
        Process->setWindowTitle(QApplication::translate("Process", "Form", 0));
        label->setText(QApplication::translate("Process", "\345\275\223\345\211\215\350\277\233\345\272\246", 0));
    } // retranslateUi

};

namespace Ui {
    class Process: public Ui_Process {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESS_H
