#pragma once

#include <QtWidgets/QMainWindow>
#include <QStateMachine>
#include "Main/labelmainwindow.h"
#include "AccountManagement/datactrl.h"
#include "ui_ZC_Label_System.h"

class ZC_Label_System : public QMainWindow
{
	Q_OBJECT

public:
	ZC_Label_System(QWidget *parent = Q_NULLPTR);

	~ZC_Label_System();


public slots:

	void OnExitStateS1(void);

	void OnEnterStateS2(void);

private:
	Ui::ZC_Label_SystemClass ui;
	QStateMachine machine;
	QState *m_s1;
	QState *m_s2;
	LabelMainWindow *m_labelMainWindow;
	DataCtrl m_iDataCtrl;
};
