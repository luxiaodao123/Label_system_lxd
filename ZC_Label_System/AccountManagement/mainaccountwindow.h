#ifndef MAINACCOUNTWINDOW_H
#define MAINACCOUNTWINDOW_H

#include <QWidget>
#include "AccountManagement/add.h"
#include "AccountManagement/modify.h"

namespace Ui {
class MainAccountWindow;
}

class MainAccountWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainAccountWindow(QWidget *parent = 0);
    ~MainAccountWindow();

private slots:


    void on_add_clicked();

    void on_modify_clicked();

private:
    Ui::MainAccountWindow *ui;
    Add *m_add;
    Modify *m_modify;
};

#endif // MAINACCOUNTWINDOW_H
