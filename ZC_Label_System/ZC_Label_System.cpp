#include "ZC_Label_System.h"
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>

ZC_Label_System::ZC_Label_System(QWidget *parent)
	: QMainWindow(parent)
{
	QIcon  *logo = new QIcon("./Resources/logo.ico");
	this->setWindowIcon(*logo);
	ui.setupUi(this);
	this->setWindowTitle(QStringLiteral("登录界面"));
	this->setFixedSize(this->size());
	ui.pwd->setEchoMode(QLineEdit::Password);
	m_s1 = new QState();
	m_s2 = new QState();
	m_labelMainWindow = new LabelMainWindow();
	machine.addState(m_s1);
	machine.addState(m_s2);

	m_s1->addTransition(ui.login, SIGNAL(clicked()), m_s2);
	// s2->addTransition(ui->pushButton, SIGNAL(clicked()), s1);

	// 分配属性
	//    s1->assignProperty(ui->pushButton, "text", "登入");
	//    s2->assignProperty(ui->pushButton, "text", "退出");
	//   s3->assignProperty(ui->pushButton, "text", "3");

	connect(m_s1, SIGNAL(exited()), this, SLOT(OnExitStateS1()));
	connect(m_s2, SIGNAL(entered()), this, SLOT(OnEnterStateS2()));

	machine.setInitialState(m_s1);
	machine.start();
}

ZC_Label_System::~ZC_Label_System()
{
	delete m_s1;
	delete m_s2;
}

void ZC_Label_System::OnExitStateS1(void)
{
	qDebug() << "Exit s1";
}

void ZC_Label_System::OnEnterStateS2(void)
{
	bool b = m_iDataCtrl.verify(ui.usr->text(), ui.pwd->text() /*QCryptographicHash::hash(ui.pwd->text().toLocal8Bit(), QCryptographicHash::Md5).toHex()*/);
	if (b != true)
	{
		QMessageBox::information(this, "tips", QString("login %1.").arg(b ? "successed" : "faild"));
		m_s2->addTransition(m_s1);
		return;
	}
	else {
		qDebug() << "Enter s2";
		m_labelMainWindow->show();
		this->hide();
	}
}

