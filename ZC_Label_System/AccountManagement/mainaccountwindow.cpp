#include "mainaccountwindow.h"
#include "ui_mainaccountwindow.h"

MainAccountWindow::MainAccountWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainAccountWindow)
{
    ui->setupUi(this);
    m_add = new Add();
    m_modify = new Modify();
}

MainAccountWindow::~MainAccountWindow()
{
    delete ui;
}

void MainAccountWindow::on_add_clicked()
{
    m_add->show();
}

void MainAccountWindow::on_modify_clicked()
{
    m_modify->show();
}
