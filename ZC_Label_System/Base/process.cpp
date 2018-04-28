#include "process.h"
#include "ui_process.h"

Process::Process(int range, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Process)
{
    ui->setupUi(this);
	ui->progressBar->setValue(0);
	ui->progressBar->setRange(0, 50000 - 1);
}

Process::~Process()
{
    delete ui;
}

void Process::setCurrentValue()
{
	//ui->progressBar->setValue(m_value);
	//m_value++;
	for (int i = 0; i < 50000; i++)
	{
		for (int j = 0; j < 20000; j++);
		ui->progressBar->setValue(i);
	}
}

void Process::setMyRange(int value)
{
	
}