#include "labelmainwindow.h"
#include "ui_labelmainwindow.h"
#include "MyLabel/dcm2image.h"
#include <iostream>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>
#include <QDate>
#include <QProgressDialog>
#include "windows.h" 
#include <QPainter> 
#include <QPen>
#include <QFont>
#include <QDesktopWidget>
#include <opencv2/opencv.hpp>
#include "PolygonContour.h"
#include <QJsonArray>


LabelMainWindow::LabelMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LabelMainWindow)
{
    ui->setupUi(this);

	_initLabelWindow();

    QIcon  *edit = new QIcon("./Resources/edit.png");
    ui->edit->setIcon(*edit);

    QIcon  *big = new QIcon("./Resources/big.png");
    ui->big->setIcon(*big);

    QIcon  *sma = new QIcon("./Resources/small.png");
    ui->sma->setIcon(*sma);

    QIcon  *save = new QIcon("./Resources/save.png");
    ui->save->setIcon(*save);

	QIcon  *logo = new QIcon("./Resources/logo.ico");
	this->setWindowIcon(*logo);

	this->setWindowTitle(QStringLiteral("糖网标注软件—智成科技"));

    _initOneEye();

	m_currentDate = _getDate();

	QSize s1 = this->size();
    this->setWindowState(Qt::WindowMaximized);
	this->move(0, 0);
	QSize s2 = this->size();
    //m_mainAccountWindow = new MainAccountWindow();

    m_add = new QAction("add", this);
 //   m_delete = new QAction("delete", this);

    ui->oneEye->setItemsExpandable(false);
    ui->listWidget->setViewMode(QListView::IconMode);
	ui->listWidget->setFlow(QListView::TopToBottom);
    //设置QListWidget中单元项的图片大小
    //设置QListWidget中单元项的间距
    ui->listWidget->setSpacing(3);
    m_isNULLImage = true;
    m_isSaved  = true;

    ui->oneEye->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOn);
    QScrollBar *HBar1 = new QScrollBar;
    ui->oneEye->setHorizontalScrollBar(HBar1);
    ui->oneEye -> header() -> setMinimumSectionSize(500);

    ui->focuslabel_1->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOn);
    QScrollBar *HBar2 = new QScrollBar;
    ui->focuslabel_1-> setHorizontalScrollBar(HBar2);
    ui->focuslabel_1-> header() -> setMinimumSectionSize(600);
	//ui->focuslabel_1 -> setSortingEnabled(false);


    connect(ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(showImage(QListWidgetItem*, QListWidgetItem*)));
    connect(ui->donot, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(changeNOPatient(QTreeWidgetItem*, QTreeWidgetItem*)));
    connect(ui->already, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(changeALPatient(QTreeWidgetItem*, int)));
    connect(ui->donot, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(changePatient(QTreeWidgetItem*, int)));
    connect(ui->paintLabel_L3, SIGNAL(changeImageSize(float)), this, SLOT(changeSize(float)));
    connect(ui->paintLabel_L3, SIGNAL(addLabel(int)), this, SLOT(treeAddLabel(int)));
    connect(ui->paintLabel_L3, SIGNAL(currentLabel(int)), this, SLOT(setcurrentLabel(int)));
    connect(ui->paintLabel_L3, SIGNAL(removeLabel(int)), this, SLOT(treeRemoveLabel(int)));
    connect(ui->donot, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(itemPressedSlot(QTreeWidgetItem*, int)));
    connect(m_add,SIGNAL(triggered()), this, SLOT(on_LoadImage()));
   // connect(m_delete,SIGNAL(triggered()), this, SLOT(deletePatient()));
    connect(ui->oneEye,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(treeItemChanged(QTreeWidgetItem*,int)));
	connect(ui->focuslabel_1, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(treeItemChanged(QTreeWidgetItem*, int)));
	connect(ui->focuslabel_1, SIGNAL(itemClicked(QTreeWidgetItem*, int )), this, SLOT(LabelChanged(QTreeWidgetItem*, int)));
	connect(ui->focuslabel_1, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(showLabel(QTreeWidgetItem*, int)));
    _loadDir("./json/no", 0);
    _loadDir("./json/yes", 1);


	


}

LabelMainWindow::~LabelMainWindow()
{

    delete ui;
}

//双窗口初始化（汕头要求）
void LabelMainWindow::_initLabelWindow()
{
	QDesktopWidget *desktop = QApplication::desktop();
	int screenCount = desktop->screenCount();
	int primScreen = desktop->primaryScreen();
	QWidget  *child = new QWidget;
	child->setWindowState(Qt::WindowMaximized);
	child->setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
	child->move(desktop->screenGeometry(primScreen + 1).width(), 0);
	child->show();
	ui->horizontalLayout_L1 = new QHBoxLayout(child);
	

	ui->font_1.setFamily(QStringLiteral("Microsoft YaHei UI"));
	ui->font_1.setPointSize(16);
	ui->scrollArea_L1 = new QScrollArea(child);
	ui->scrollArea_L1->setObjectName(QStringLiteral("scrollArea_L1"));
	ui->scrollArea_L1->setMinimumSize(QSize(0, 0));
	ui->scrollArea_L1->setStyleSheet(QLatin1String("QScrollArea{  \n"
		"        background-color: #ffffff;  \n"
		"} "));
	ui->scrollArea_L1->setWidgetResizable(true);
	ui->scrollAreaWidgetContents_L2 = new QWidget();
	ui->scrollAreaWidgetContents_L2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
	ui->scrollAreaWidgetContents_L2->setGeometry(QRect(0, 0, 1772, 1165));
	ui->paintLabel_L3 = new PaintLabel(ui->scrollAreaWidgetContents_L2);
	ui->paintLabel_L3->setObjectName(QStringLiteral("paintLabel_L3"));
	ui->paintLabel_L3->setGeometry(QRect(0, 0, 1000, 666));
	ui->paintLabel_L3->setStyleSheet(QLatin1String("QScrollArea{  \n"
		"        background-color: #ffffff;  \n"
		"} \n"
		""));
	ui->scrollArea_L1->setWidget(ui->scrollAreaWidgetContents_L2);

	ui->horizontalLayout_L1->addWidget(ui->scrollArea_L1);

	ui->focuslabel_1 = new QTreeWidget(child);
	QTreeWidgetItem *__qtreewidgetitem_L1 = new QTreeWidgetItem();
	__qtreewidgetitem_L1->setFont(0, ui->font_1);
	ui->focuslabel_1->setHeaderItem(__qtreewidgetitem_L1);
	ui->focuslabel_1->setObjectName(QStringLiteral("focuslabel_1"));
	ui->focuslabel_1->setMinimumSize(QSize(250, 0));
	ui->focuslabel_1->setMaximumSize(QSize(200, 16777215));
	ui->focuslabel_1->setStyleSheet(QLatin1String("    QTreeWidget{  \n"
		"	   font: 75 14pt \"Microsoft JhengHei UI\";\n"
		"        background-color: #ffffff;  \n"
		"      \n"
		"        /* set the font properties*/  \n"
		"        /*font-size:17px;  */\n"
		"        color: black;\n"
		"    } \n"
		"\n"
		"QTreeWidget::item:hover {  \n"
		"    background: #d8dbdd;  \n"
		"}  \n"
		"  \n"
		"QTreeWidget::item:selected:active{  \n"
		"   /* background: #5a8ae0;  */\n"
		"}  \n"
		"  \n"
		"QTreeWidget::item::true {  \n"
		"    /*background: rgb(63, 147, 168); */ 	\n"
		"}"));
	ui->horizontalLayout_L1->addWidget(ui->focuslabel_1);
	ui->focuslabel_1->setHeaderLabel(QStringLiteral("标记区域"));
}


//json数据处理函数
void LabelMainWindow::_loadNo(QString ID, QTreeWidgetItem *currentDate)
{
	for (int i = 0; i < currentDate->childCount(); i++)
	{
		if (ID == currentDate->child(i)->text(0))
		{
			return;
		}
	}
	QTreeWidgetItem* name = new QTreeWidgetItem(currentDate);
	name->setText(0, ID);
	name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	name->setFlags(name->flags() & (~Qt::ItemIsEditable));

	//QStringList IDlist = m_patientImageList[ID];
	//if (IDlist.count() == 0)
	//	return;
	//for (int i = 0; i < IDlist.count(); i++)
	//{
	//	ImageInfo info = m_imageInfo[IDlist.at(i).section('/', -1)];
	//	if (info.getState() == false)
	//		return;
	//}

	//for (int i = 0; i < currentDate->childCount(); i++)
	//{
	//	if (currentDate->child(i)->text(0) == ID)
	//	{
	//		delete currentDate->child(i);
	//		break;
	//	}
	//}

	//QTreeWidgetItem *alCurrentDate = _createDateInAl(currentDate->text(0));
	//for (int i = 0; i < alCurrentDate->childCount(); i++)
	//{
	//	if (ID == alCurrentDate->child(i)->text(0))
	//	{
	//		return;
	//	}
	//}

	//QTreeWidgetItem* name1 = new QTreeWidgetItem(alCurrentDate);
	//name1->setText(0, ID);
	//name1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	//name1->setFlags(name->flags() & (~Qt::ItemIsEditable));
}

void LabelMainWindow::_loadYes(QString ID, QTreeWidgetItem *currentDate)
{
	for (int i = 0; i < currentDate->childCount(); i++)
	{
		if (ID == currentDate->child(i)->text(0))
		{
			return;
		}
	}
	QTreeWidgetItem* name = new QTreeWidgetItem(currentDate);
	name->setText(0, ID);
	name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	name->setFlags(name->flags() & (~Qt::ItemIsEditable));

}

void LabelMainWindow::_loadJsonNo(QString path)
{
	QTreeWidgetItem *currentDate = _createDateInNO(path.section('/', -1));
	QDir dir(path);
	foreach(QFileInfo mfi, dir.entryInfoList())
	{
		if (!mfi.isFile())
		{
			if (mfi.fileName() == "." || mfi.fileName() == "..")
				continue;
			QString ID = mfi.absoluteFilePath().section("/", -1);
			m_dateFromID.insert(ID, path.section('/', -1));
			QDir dir1(mfi.absoluteFilePath());
			QStringList tempList;
			QString tempPath;
			foreach(QFileInfo mfi1, dir1.entryInfoList())
			{
				if (mfi1.isFile() && mfi1.absoluteFilePath().section(".", -1) == "json")
				{
					tempPath = mfi1.absoluteFilePath();
				}
				else if (mfi1.isFile() && mfi1.absoluteFilePath().section(".", -1) != "json")
				{
					tempList.push_back(mfi1.absoluteFilePath().section("/", -1));
				}
				else {}
			}
			m_patientImageList.insert(ID, tempList);
			_parse(tempPath, ID, "no");
			_loadNo(ID, currentDate);
			m_IDflag.insert(ID, "no");
		}
	}
}

void LabelMainWindow::_loadJsonYes(QString path)
{
	QTreeWidgetItem *currentDate = _createDateInAl(path.section('/', -1));
	QDir dir(path);
	foreach(QFileInfo mfi, dir.entryInfoList())
	{
		if (!mfi.isFile())
		{
			if (mfi.fileName() == "." || mfi.fileName() == "..")
				continue;
			QString ID = mfi.absoluteFilePath().section("/", -1);
			m_dateFromID.insert(ID, path.section('/', -1));
			QDir dir1(mfi.absoluteFilePath());
			QStringList tempList;
			QString tempPath;
			foreach(QFileInfo mfi1, dir1.entryInfoList())
			{
				if (mfi1.isFile() && mfi1.absoluteFilePath().section(".", -1) == "json")
				{
					tempPath = mfi1.absoluteFilePath();
				}
				else if (mfi1.isFile() && mfi1.absoluteFilePath().section(".", -1) != "json")
				{
					tempList.push_back(mfi1.absoluteFilePath().section("/", -1));
				}
				else {}
			}
			m_patientImageList.insert(ID, tempList);
			_parse(tempPath, ID, "yes");
			_loadYes(ID, currentDate);
			m_IDflag.insert(ID, "yes");
		}
	}
}

void LabelMainWindow::_loadDir(QString path, int flag)
{
    QDir dir(path);
    foreach(QFileInfo mfi ,dir.entryInfoList())
    {
		
      if(!mfi.isFile())
      {
		  if (mfi.fileName() == "." || mfi.fileName() == "..")
			  continue;
          if(flag == 0)
          {
			  _loadJsonNo(mfi.absoluteFilePath());
          }
          else
          {
			  _loadJsonYes(mfi.absoluteFilePath());
          }
      }
    }
}

void LabelMainWindow::_parse(QString path, QString ID, QString flag)
{
    QStringList list = m_patientImageList.value(ID);
    QString val;
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    if (doc.isObject())
    {
        QJsonObject Tree = doc.object();
        QJsonObject::iterator TreeIt = Tree.begin();
        while(TreeIt != Tree.end())
        {
			ImageInfo info = m_imageInfo.value(TreeIt.key());
			info.setJsonValue(TreeIt.value());
			info.setJsonFlag(false);
            list.push_back(TreeIt.key());
            //_parseImg(TreeIt.value(), flag, ID);
			m_imageInfo.insert(TreeIt.key(), info);
            TreeIt++;
        }

    }
   // m_patientImageList[ID] = list;
}

void LabelMainWindow::_parseImg(QJsonValue root, QString flag, QString ID)
{

    QJsonObject childObj = root.toObject();
    QString imgName;
    float step;
    int index;
    QVector<QPointF> pointVec;
    QMap<int, QPolygonF> polyPool;
	if (childObj.contains("disease"))
	{
		QJsonValue childvalue = childObj.value("disease");
		QJsonObject child2Obj = childvalue.toObject();
		if (child2Obj.contains(QStringLiteral("无病变")))
		{

			m_disease.push_back(QStringLiteral("无病变"));
		}

		if (child2Obj.contains(QStringLiteral("动脉硬化高血压眼底")))
		{

			m_disease.push_back(QStringLiteral("动脉硬化高血压眼底"));
		}

		if (child2Obj.contains(QStringLiteral("青光眼")))
		{

			m_disease.push_back(QStringLiteral("青光眼"));
		}

		if (child2Obj.contains(QStringLiteral("白内障")))
		{

			m_disease.push_back(QStringLiteral("白内障"));
		}

		if (child2Obj.contains(QStringLiteral("老年性眼底黄斑变性")))
		{

			m_disease.push_back(QStringLiteral("老年性眼底黄斑变性"));
		}

		if (child2Obj.contains(QStringLiteral("病理性近视")))
		{

			m_disease.push_back(QStringLiteral("病理性近视"));
		}

		if (child2Obj.contains(QStringLiteral("视网膜血管阻塞")))
		{

			m_disease.push_back(QStringLiteral("视网膜血管阻塞"));
		}

		if (child2Obj.contains(QStringLiteral("玻璃体疾病")))
		{

			m_disease.push_back(QStringLiteral("玻璃体疾病"));
		}

		if (child2Obj.contains(QStringLiteral("脉络膜疾病")))
		{

			m_disease.push_back(QStringLiteral("脉络膜疾病"));
		}

		if (child2Obj.contains(QStringLiteral("视神经疾病")))
		{

			m_disease.push_back(QStringLiteral("视神经疾病"));
		}

		if (child2Obj.contains(QStringLiteral("糖网病变")))
		{

			m_disease.push_back(QStringLiteral("糖网病变"));
		}

		if (child2Obj.contains(QStringLiteral("其他")))
		{

			m_disease.push_back(QStringLiteral("其他"));
		}
		
	}
        if(childObj.contains("step"))
        {
            step = childObj.value("step").toDouble();
        }

        if(childObj.contains("index"))
        {
            index = childObj.value("index").toDouble();
        }

        if(childObj.contains("path"))
        {
            imgName = childObj.value("path").toString();
        }

        if(childObj.contains(QStringLiteral("眼别")))
        {

            m_OneEye.insert(QStringLiteral("眼别"), childObj.value(QStringLiteral("眼别")).toString());
        }

        if(childObj.contains(QStringLiteral("图片质量")))
        {

            m_OneEye.insert(QStringLiteral("图片质量"), childObj.value(QStringLiteral("图片质量")).toString());
        }

        if(childObj.contains(QStringLiteral("图片位置")))
        {

            m_OneEye.insert(QStringLiteral("图片位置"), childObj.value(QStringLiteral("图片位置")).toString());
        }

        if(childObj.contains(QStringLiteral("糖网分期")))
        {

            m_OneEye.insert(QStringLiteral("糖尿病视网膜病变"), childObj.value(QStringLiteral("糖网分期")).toString());
        }

		if (childObj.contains(QStringLiteral("糖尿病视网膜病变")))
		{

			m_OneEye.insert(QStringLiteral("糖尿病视网膜病变"), childObj.value(QStringLiteral("糖尿病视网膜病变")).toString());
		}

        if(childObj.contains(QStringLiteral("DME")))
        {

            m_OneEye.insert(QStringLiteral("糖尿病性黄斑水肿"), childObj.value(QStringLiteral("DME")).toString());
        }

		if (childObj.contains(QStringLiteral("糖尿病性黄斑水肿")))
		{

			m_OneEye.insert(QStringLiteral("糖尿病性黄斑水肿"), childObj.value(QStringLiteral("糖尿病性黄斑水肿")).toString());
		}

		if (childObj.contains(QStringLiteral("激光斑")))
		{

			m_OneEye.insert(QStringLiteral("激光斑"), childObj.value(QStringLiteral("激光斑")).toString());
		}

		
        if(childObj.contains("region"))
        {
            QJsonValue childvalue = childObj.value("region");
            QJsonObject child2Obj = childvalue.toObject();
            QJsonObject::Iterator it;
            for(it = child2Obj.begin(); it != child2Obj.end(); it++)
            {
                QJsonObject child3Obj = it.value().toObject();
                if(child3Obj.contains("name"))
                {
                    m_checked.insert(it.key(), child3Obj.value(QStringLiteral("name")).toString());
                }

                if(child3Obj.contains("coordinate"))
                {
                    //qDebug() << "coordinate";
                    QJsonValue codvalue = child3Obj.value("coordinate");
                    QJsonObject  codobj = codvalue.toObject();
                    int j = 1;
                    while(j)
                    {
                        if(!codobj.contains(QString::number(j, 10)))
                        {
                            //qDebug() << j;
                            break;
                        }
                        QJsonValue pointValue = codobj.value(QString::number(j, 10));
                        QJsonObject pointObj = pointValue.toObject();

                        pointVec.push_back(QPointF(pointObj.value("x:").toDouble(), pointObj.value("y:").toDouble()));
                        QVector<QPointF> tempVec = pointVec;
                       // qDebug() << tempVec;
                        QPolygonF *poly = new QPolygonF(tempVec);
                        polyPool.insert(it.key().toInt(), *poly);
                        delete poly;
                        j++;

                    }
                    pointVec.clear();
                }
            }

        }
		
		QString date = m_dateFromID.value(ID);
		QString newpath = "./json/" + flag + "/" + date + "/" + ID + "/" + imgName;
		ImageInfo info = m_imageInfo.value(newpath.section('/', -1));
		info.setOneEye(m_OneEye);
		info.setFocusInfo(m_checked);
		info.setDisease(m_disease);
		info.setStep(1.0);
		info.setPoly(polyPool);
		info.setIndex(index);
		info.setJsonFlag(true);
		if (index != 0 || m_OneEye.count() != 0)
		{
			info.setState(true);
		}
		QString dcm = newpath.section(".", -1);
		if (dcm == "dcm")
		{
			QImage image(*Dcm2Image(newpath).getImage());
			ui->paintLabel_L3->BackImage(image);
		}
		else
		{
			ui->paintLabel_L3->BackImage(newpath);
		}
		m_origin = new QImage(ui->paintLabel_L3->OriPic());
		info.setOrigin(*m_origin);

		m_imageInfo.insert(newpath.section('/', -1), info);
		m_OneEye.clear();
		m_disease.clear();
		m_checked.clear();
}


void LabelMainWindow::_initOneEye()
{
	ui->oneEye->clear();
	//QTreeWidgetItem* name_1 = new QTreeWidgetItem(ui->oneEye);
	//name_1->setText(0, QStringLiteral("疾病"));    //树形控件显示的文本信息


	//QTreeWidgetItem* name_1_1 = new QTreeWidgetItem(name_1);
	//name_1_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//name_1_1->setText(0, QStringLiteral("无病变"));  //设置子项显示的文本
	//name_1_1->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

	//QTreeWidgetItem* name_1_2 = new QTreeWidgetItem(name_1);
	//name_1_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//name_1_2->setText(0, QStringLiteral("动脉硬化高血压眼底"));  //设置子项显示的文本
	//name_1_2->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

	//QTreeWidgetItem* name_1_3 = new QTreeWidgetItem(name_1);
	//name_1_3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//name_1_3->setText(0, QStringLiteral("青光眼"));  //设置子项显示的文本
	//name_1_3->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

	//QTreeWidgetItem* name_1_4 = new QTreeWidgetItem(name_1);
	//name_1_4->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//name_1_4->setText(0, QStringLiteral("白内障"));  //设置子项显示的文本
	//name_1_4->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

	//QTreeWidgetItem* name_1_5 = new QTreeWidgetItem(name_1);
	//name_1_5->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//name_1_5->setText(0, QStringLiteral("老年性眼底黄斑变性"));  //设置子项显示的文本
	//name_1_5->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

	//QTreeWidgetItem* name_1_6 = new QTreeWidgetItem(name_1);
	//name_1_6->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//name_1_6->setText(0, QStringLiteral("病理性近视"));  //设置子项显示的文本
	//name_1_6->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

	//QTreeWidgetItem* name_1_7 = new QTreeWidgetItem(name_1);
	//name_1_7->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//name_1_7->setText(0, QStringLiteral("视网膜血管阻塞"));  //设置子项显示的文本
	//name_1_7->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

	//QTreeWidgetItem* name_1_8 = new QTreeWidgetItem(name_1);
	//name_1_8->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//name_1_8->setText(0, QStringLiteral("玻璃体疾病"));  //设置子项显示的文本
	//name_1_8->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

	//QTreeWidgetItem* name_1_9 = new QTreeWidgetItem(name_1);
	//name_1_9->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//name_1_9->setText(0, QStringLiteral("脉络膜疾病"));  //设置子项显示的文本
	//name_1_9->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

	//QTreeWidgetItem* name_1_10 = new QTreeWidgetItem(name_1);
	//name_1_10->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//name_1_10->setText(0, QStringLiteral("视神经疾病"));  //设置子项显示的文本
	//name_1_10->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

	//QTreeWidgetItem* name_1_11 = new QTreeWidgetItem(name_1);
	//name_1_11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//name_1_11->setText(0, QStringLiteral("糖网病变"));  //设置子项显示的文本
	//name_1_11->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

	//QTreeWidgetItem* name_1_12 = new QTreeWidgetItem(name_1);
	//name_1_12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//name_1_12->setText(0, QStringLiteral("其他"));  //设置子项显示的文本
	//name_1_12->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态


												//name_2树形组
	QTreeWidgetItem* name_2 = new QTreeWidgetItem(ui->oneEye);
	name_2->setText(0, QStringLiteral("眼别"));    //树形控件显示的文本信息


												 //眼別子项
	QTreeWidgetItem* name_2_1 = new QTreeWidgetItem(name_2);
	name_2_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_2_1->setText(0, QStringLiteral("左眼"));  //设置子项显示的文本
	name_2_1->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

	QTreeWidgetItem* name_2_2 = new QTreeWidgetItem(name_2);
	name_2_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_2_2->setText(0, QStringLiteral("右眼"));
	name_2_2->setCheckState(0, Qt::Unchecked);

	//QTreeWidgetItem* name_2_3 = new QTreeWidgetItem(name_2);
	//name_2_3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//name_2_3->setText(0, QStringLiteral("无法判别"));
	//name_2_3->setCheckState(0, Qt::Unchecked);

	//name_3树形组
	QTreeWidgetItem* name_3 = new QTreeWidgetItem(ui->oneEye);
	name_3->setText(0, QStringLiteral("图片质量"));


	//name_3子项
	QTreeWidgetItem* name_3_1 = new QTreeWidgetItem(name_3);//指定子项属于哪一个父项
	name_3_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_3_1->setText(0, QStringLiteral("清晰可见"));
	name_3_1->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* name_3_2 = new QTreeWidgetItem(name_3);
	name_3_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_3_2->setText(0, QStringLiteral("可以评级"));
	name_3_2->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* name_3_3 = new QTreeWidgetItem(name_3);
	name_3_3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_3_3->setText(0, QStringLiteral("无法评级"));
	name_3_3->setCheckState(0, Qt::Unchecked);

	//name_4树形组
	QTreeWidgetItem* name_4 = new QTreeWidgetItem(ui->oneEye);
	name_4->setText(0, QStringLiteral("图片位置"));


	//name_4子项
	QTreeWidgetItem* name_4_1 = new QTreeWidgetItem(name_4);//指定子项属于哪一个父项
	name_4_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_4_1->setText(0, QStringLiteral("黄斑为中心"));
	name_4_1->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* name_4_2 = new QTreeWidgetItem(name_4);
	name_4_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_4_2->setText(0, QStringLiteral("视盘为中心"));
	name_4_2->setCheckState(0, Qt::Unchecked);

	for (int i = 1; i > 0; i--) {
		QTreeWidgetItem* name_1_12 = new QTreeWidgetItem(name_4);
		name_1_12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		name_1_12->setText(0, QStringLiteral("其他"));
		name_1_12->setCheckState(0, Qt::Unchecked);
	}


	QTreeWidgetItem* name_5 = new QTreeWidgetItem(ui->oneEye);   //指定子项属于哪一个父项
	name_5->setText(0, QStringLiteral("糖尿病视网膜病变"));

	//name_5子项
	QTreeWidgetItem* name_5_1 = new QTreeWidgetItem(name_5);   //指定子项属于哪一个父项
	name_5_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_5_1->setText(0, QStringLiteral("无视网膜病变"));
	name_5_1->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* name_5_2 = new QTreeWidgetItem(name_5);   //指定子项属于哪一个父项
	name_5_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_5_2->setText(0, QStringLiteral("轻度非增殖性糖尿病视网膜病变"));
	name_5_2->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* name_5_3 = new QTreeWidgetItem(name_5);   //指定子项属于哪一个父项
	name_5_3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_5_3->setText(0, QStringLiteral("中度非增殖性糖尿病视网膜病变"));
	name_5_3->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* name_5_4 = new QTreeWidgetItem(name_5);   //指定子项属于哪一个父项
	name_5_4->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_5_4->setText(0, QStringLiteral("重度非增殖性糖尿病视网膜病变"));
	name_5_4->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* name_5_5 = new QTreeWidgetItem(name_5);   //指定子项属于哪一个父项
	name_5_5->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_5_5->setText(0, QStringLiteral("增殖性糖尿病视网膜病变"));
	name_5_5->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* DME = new QTreeWidgetItem(ui->oneEye);   //指定子项属于哪一个父项
															  //    DME->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	DME->setText(0, QStringLiteral("糖尿病性黄斑水肿"));
	//    DME->setCheckState(0,Qt::Unchecked);

	//DME子项
	QTreeWidgetItem* name_6_1 = new QTreeWidgetItem(DME);   //指定子项属于哪一个父项
	name_6_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_6_1->setText(0, QStringLiteral("无明显的DME"));
	name_6_1->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* name_6_2 = new QTreeWidgetItem(DME);   //指定子项属于哪一个父项
	name_6_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_6_2->setText(0, QStringLiteral("轻度DME"));
	name_6_2->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* name_6_3 = new QTreeWidgetItem(DME);   //指定子项属于哪一个父项
	name_6_3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_6_3->setText(0, QStringLiteral("中度DME"));
	name_6_3->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* name_6_4 = new QTreeWidgetItem(DME);   //指定子项属于哪一个父项
	name_6_4->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_6_4->setText(0, QStringLiteral("重度DME"));
	name_6_4->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* name_7 = new QTreeWidgetItem(ui->oneEye);   //指定子项属于哪一个父项
	name_7->setText(0, QStringLiteral("激光斑"));

	QTreeWidgetItem* name_7_1 = new QTreeWidgetItem(name_7);   //指定子项属于哪一个父项
	name_7_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_7_1->setText(0, QStringLiteral("无明显激光瘢痕"));
	name_7_1->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* name_7_2 = new QTreeWidgetItem(name_7);   //指定子项属于哪一个父项
	name_7_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_7_2->setText(0, QStringLiteral("黄斑区局部或者格栅样光凝"));
	name_7_2->setCheckState(0, Qt::Unchecked);

	QTreeWidgetItem* name_7_3 = new QTreeWidgetItem(name_7);   //指定子项属于哪一个父项
	name_7_3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	name_7_3->setText(0, QStringLiteral("周边视网膜光凝或者全视网膜光凝"));
	name_7_3->setCheckState(0, Qt::Unchecked);

	ui->oneEye->expandAll();
}

void LabelMainWindow::_setLabelGeometry()
{
	int x = ui->scrollArea_L1->width() - ui->paintLabel_L3->width();
	int y = ui->scrollArea_L1->height() - ui->paintLabel_L3->height();
	if (x < 0)
	{
		x = 0;
	}
	if (y < 0)
	{
		y = 0;
	}
	
	ui->paintLabel_L3->setGeometry(x / 2, y / 2, ui->paintLabel_L3->width(), ui->paintLabel_L3->height());
}

void LabelMainWindow::_createPatient(QString ID, int flag)
{

	
	ui->listWidget->clear();
	int listHeight = ui->listWidget->height();
	int iconWidth = listHeight * 1.0f;
	int iconHeight = listHeight * 0.75f;
	ui->listWidget->setIconSize(QSize(iconWidth, iconHeight));

    QStringList tempList = m_patientImageList.value(ID);
	QString date = m_dateFromID.value(ID);
    for (int i = 0; i < tempList.count(); i++)
    {
		DWORD stopTime;
		DWORD startTime = GetTickCount();
		QString path;
		if(flag ==  0)
			path = "./json/no/" + date + "/" + ID + "/" + tempList.at(i).section("/", -1);
		else
			path = "./json/yes/" + date + "/" + ID + "/" + tempList.at(i).section("/", -1);
		QListWidgetItem *imageItem = new QListWidgetItem;
        QString dcm = path.section(".", -1);
        if (dcm == "dcm")
        {
            QImage image(*Dcm2Image(path).getImage());
            imageItem->setIcon(QIcon(QPixmap::fromImage(image)));
        }
        else
        {
			//DWORD stopTime;
			//DWORD startTime = GetTickCount();
            imageItem->setIcon(QIcon(path));
			//stopTime = GetTickCount();
			//qDebug() << "GetTickCount1 = " << (stopTime - startTime) << "ms";
        }
		//imageItem->setTextAlignment(Qt::AlignBottom);
        imageItem->setText(path);
        imageItem->setSizeHint(QSize(iconWidth, iconHeight + 20));
		imageItem->setFlags(imageItem->flags() & (~Qt::ItemIsDragEnabled));;
        ui->listWidget->addItem(imageItem);

		stopTime = GetTickCount();
		qDebug() << "GetTickCount1 = " << (stopTime - startTime) << "ms";

		
		if (!m_imageInfo.contains(path.section('/', -1)) || m_imageInfo.value(path.section('/', -1)).getJsonFlag() == false)
		{
			ImageInfo imageinfo = m_imageInfo.value(path.section('/', -1));
			m_OneLabelChecked.clear();
            m_OneEye.clear();

			ui->paintLabel_L3->BackImage(path);
			ui->paintLabel_L3->resize(ui->paintLabel_L3->size());
			QImage origin(ui->paintLabel_L3->OriPic());

			imageinfo.setOrigin(origin);
            imageinfo.setOneEye(m_OneEye);
			m_imageInfo.insert(path.section('/', -1), imageinfo);
		}

    }
	
}

void LabelMainWindow::_saveOneImg(QString flag, QString ID, QString imgName)
{
	QString val;
	QFile file;
	QString jsonPath = "./json/" + flag + "/" + m_dateFromID.value(ID) + "/" + ID + "/" + "result.json";
	file.setFileName(jsonPath);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	val = file.readAll();
	file.close();

	QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
	QJsonObject Tree(doc.object());
	_saveImageInfo(&Tree, imgName);
	QJsonDocument jsonDoc(Tree);
    QByteArray ba = jsonDoc.toJson();
	QFile file1(jsonPath);
	if (!file1.open(QIODevice::WriteOnly))
	{
		return;
	}
	file1.write(ba);
	file1.close();

}

void LabelMainWindow::_saveImageInfo(QJsonObject *PatientID, QString imagename)
{
    ImageInfo info = m_imageInfo[imagename.section('/', -1)];

    QJsonObject *json = new QJsonObject;
    QJsonObject *region  = new QJsonObject;
    QMap<QString, QString> OneEye = info.getOneEye();
    QMap<QString, QString>::iterator oneEyeIt = OneEye.begin();
    while(oneEyeIt != OneEye.end())
    {
        json->insert(oneEyeIt.key(), oneEyeIt.value());
        oneEyeIt++;
    }
	QList<QString> disease = info.getDisease();
	QList<QString>::iterator diseaseIt = disease.begin();
	QJsonObject *eyeDisease = new QJsonObject;
	int diseaseNUm = 1;
	while (diseaseIt != disease.end())
	{
		eyeDisease->insert(*diseaseIt, diseaseNUm++);
		diseaseIt++;
	}
	json->insert("disease", *eyeDisease);


    json->insert("path", imagename.section('/', -1));
    QMap<int, QPolygonF> poly = info.getPoly();
    QMap<int, QPolygonF>::iterator it = poly.begin();
    while(it != poly.end())
    {
        char a[11];
        const char *p = itoa(it.key(), a, 10);
        QString stringP = p;


        QJsonObject *tempJson  = new QJsonObject;
        QJsonObject *labelname  = new QJsonObject;
        QJsonObject *cod = new QJsonObject;
        QJsonObject *codObj = new QJsonObject;
        QPolygonF polygonF = it.value();
        int codNum = 1;
        for(int j = 0; j < polygonF.count(); j++)
        {
            codObj->insert("x:", polygonF[j].x());
            codObj->insert("y:", polygonF[j].y());
            cod->insert(QString::number(codNum++, 10), *codObj);
        }

        QMap<QString, QString> foucus = info.getFocusInfo();
        QMap<QString, QString>::iterator foucusIt = foucus.begin();
        while(foucusIt != foucus.end())
        {
            if(foucusIt.key() == stringP)
            {
                tempJson->insert("name", foucusIt.value());
                break;
            }
            foucusIt++;
        }

        tempJson->insert("coordinate", *cod);
        region->insert(p, *tempJson);
        it++;
        delete cod;
        delete codObj;
        delete tempJson;
    }


    QMap<QString, Shape> shape = info.getShape();
    QMap<QString, Shape>::iterator shapeIt = shape.begin();
    while(shapeIt != shape.end())
    {
        QJsonObject *tempJson  = new QJsonObject;
        QMap<QString, QString> foucus = info.getFocusInfo();
        QMap<QString, QString>::iterator foucusIt = foucus.begin();
        while(foucusIt != foucus.end())
        {
            if(foucusIt.key() == shapeIt.key())
            {
                tempJson->insert("name", foucusIt.value());
                break;
            }
            foucusIt++;
        }

        tempJson->insert("cx", shapeIt.value().getCX());
        tempJson->insert("cy", shapeIt.value().getCY());
        tempJson->insert("r", shapeIt.value().getR());

        region->insert(shapeIt.key(), *tempJson);
        shapeIt++;
    }


    json->insert("region", *region);
    json->insert("step", info.getStep());
    json->insert("index", info.getIndex());
    PatientID->insert(imagename.section('/', -1), *json);
    delete region;
    delete json;
}

void LabelMainWindow::_changeOneEyeLabel(int flag)
{
    for(int i = 0; i < ui->oneEye->topLevelItemCount(); i++)
    {
        QTreeWidgetItem* parent = ui->oneEye->topLevelItem(i);
        int count = parent->childCount();
        for(int j = 0; j < count; j++)
        {
            if(parent->child(j)->checkState(0) == Qt::Checked)
            {
				if (parent->text(0) == QStringLiteral("疾病"))
				{
					m_disease.push_back(parent->child(j)->text(0));
				}
				else 
				{
					m_OneEye.insert(parent->text(0), parent->child(j)->text(0));
				}
				if(flag == 1)
					parent->child(j)->setCheckState(0, Qt::Unchecked);
				parent->child(j)->setBackgroundColor(0, QColor(255, 255, 255));
            }
        }
    }
}

void LabelMainWindow::_changeFocuslabel(QTreeWidgetItem* node, int flag)
{
	qDebug() << node->text(0);
    if(node->childCount() > 0)
    {
        QString check;
        for(int i = 0; i < node->childCount(); i++)
        {
            if(node->child(i)->checkState(0)== Qt::Checked)
            {
                check = node->child(i)->text(0);
            }
			if (flag == 1)
			{
				_del(node->child(i));
				i--;
			}
			m_checked.insert(node->text(0), check);
        }
        
    }
	if(flag == 1)
		delete node;
}

void LabelMainWindow::_del(QTreeWidgetItem* node)
{     
	for(int i = 0; i < node->childCount(); i++)    
	{   
		_del(node->child(i));     
		i--;   
	}
    delete node;
}

void LabelMainWindow::_addLabel(QString str)
{
	QStringList rootName_1;
	rootName_1.push_back(str);
	QTreeWidgetItem *rootItem_1 = new QTreeWidgetItem(ui->focuslabel_1, rootName_1);

    QTreeWidgetItem* rootItem_1_1 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_1->setText(0,QStringLiteral("微动脉瘤(Microaneurysms)或者出血点(Hemorrhages Spot)"));  //设置子项显示的文本
    rootItem_1_1->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_2 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_2->setText(0,QStringLiteral("硬性渗出(Hard Exudate)"));  //设置子项显示的文本
    rootItem_1_2->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

	QTreeWidgetItem* rootItem_1_18 = new QTreeWidgetItem(rootItem_1);
	rootItem_1_18->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	rootItem_1_18->setText(0, QStringLiteral("微动脉瘤(Microaneurysms)"));  //设置子项显示的文本
	rootItem_1_18->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_3 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_3->setText(0,QStringLiteral("出血(Hemorrhages)"));  //设置子项显示的文本
    rootItem_1_3->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_4 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_4->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_4->setText(0,QStringLiteral("棉绒斑(Cotton Wool Spot)"));  //设置子项显示的文本
    rootItem_1_4->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_5 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_5->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_5->setText(0,QStringLiteral("静脉襻(Venous Loop)"));  //设置子项显示的文本
    rootItem_1_5->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_6 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_6->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_6->setText(0,QStringLiteral("墨渍样出血(Blot Hemorrhages)"));  //设置子项显示的文本
    rootItem_1_6->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_7 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_7->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_7->setText(0,QStringLiteral("静脉串珠(Venous Beading)"));  //设置子项显示的文本
    rootItem_1_7->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_8 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_8->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_8->setText(0,QStringLiteral("静脉复制(Venous Reproduction)"));  //设置子项显示的文本
    rootItem_1_8->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_9 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_9->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_9->setText(0,QStringLiteral("视网膜内微血管异常(IRMA - Intraretinal Microvascular Abnormities)"));  //设置子项显示的文本
    rootItem_1_9->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_10 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_10->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_10->setText(0,QStringLiteral("视网膜前出血(Pre Retinal Hemorrhages)"));  //设置子项显示的文本
    rootItem_1_10->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_11 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_11->setText(0,QStringLiteral("玻璃体出血(Vitreous Hemorrhages)"));  //设置子项显示的文本
    rootItem_1_11->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_12 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_12->setText(0,QStringLiteral("新生血管(New Vessels)"));  //设置子项显示的文本
    rootItem_1_12->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_13 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_13->setText(0,QStringLiteral("增殖膜(Fibrous Proliferation)"));  //设置子项显示的文本
    rootItem_1_13->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_14 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_14->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_14->setText(0,QStringLiteral("视盘(Optic Disk)"));  //设置子项显示的文本
    rootItem_1_14->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_15 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_15->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_15->setText(0,QStringLiteral("黄斑中央凹(Central Foveal Thickness)"));  //设置子项显示的文本
    rootItem_1_15->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_16 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_16->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_16->setText(0,QStringLiteral("激光斑(Laser Spot)"));  //设置子项显示的文本
    rootItem_1_16->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态


    QTreeWidgetItem* rootItem_1_17 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_17->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_17->setText(0,QStringLiteral("other"));  //设置子项显示的文本
    rootItem_1_17->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    ui->focuslabel_1->update();

}

void LabelMainWindow::_createDirByID(QString path, QStringList list)
{
	QDir *dir = new QDir;
	if (!dir->exists(path))
	{
		bool ok = dir->mkdir(path);
	}
	for (int j = 0; j < list.count(); j++)
	{	
		QString filename = path + "/" + list.at(j).section('/', -1);
		QDir *createfile = new QDir;
		bool exist = createfile->exists(filename);
		if (exist) 
		{
			createfile->remove(filename);

		}
		bool exist2 = createfile->exists(list.at(j));
		if (!exist2)
		{
			continue;
		}
		if (!QFile::copy(list.at(j), filename))
		{
			QMessageBox::warning(this, tr("warning"), "file no exits!", QMessageBox::Yes);
		}
		//createfile->remove("./img/" + list.at(j));
		delete createfile;
	}
	delete dir;

}

void LabelMainWindow::_moveNoToYes(QString ID)
{
	QDir *dir = new QDir;
	QString DateFile = "./json/yes/" + m_dateFromID.value(ID);
	if (!dir->exists(DateFile))
	{
		bool ok = dir->mkdir(DateFile);
	}
	if (!dir->exists(DateFile + "/" + ID))
	{
		bool ok = dir->mkdir(DateFile + "/" + ID);
	}
	QStringList list = m_patientImageList.value(ID);
	for (int i = 0; i < list.count(); i++)
	{
		QString src = "./json/no/" + m_dateFromID.value(ID) + "/" + ID + "/" + list.at(i).section('/', -1);
		QString dst = DateFile + "/" + ID + "/" + list.at(i).section('/', -1);
		QDir *createfile = new QDir;
		if (!QFile::copy(src, dst))
		{
			QMessageBox::warning(this, tr("warning"), "file no exits!", QMessageBox::Yes);
		}
		createfile->remove(src);
		delete createfile;
	}
	QString jsonSrc = "./json/no/" + m_dateFromID.value(ID) + "/" + ID +"/" + "result.json";
	QString jsonDst = DateFile + "/" + ID + "/" + "result.json";
	QDir *json = new QDir;
	if (!QFile::copy(jsonSrc, jsonDst))
	{
		QMessageBox::warning(this, tr("warning"), "file no exits!", QMessageBox::Yes);
	}
	json->remove(jsonSrc);
	bool ok = dir->rmdir("./json/no/" + m_dateFromID.value(ID) + "/" + ID);
	delete json;
	delete dir;
}

QString LabelMainWindow::_getDate()
{
	QDateTime currentDateTime = QDateTime::currentDateTime();
	QString currentDate = currentDateTime.toString("yyyy_MM_dd");
	return currentDate;
}

QTreeWidgetItem *LabelMainWindow::_createDateInNO(QString date)
{
	int i = 0;
	QTreeWidgetItem *currentDate;

	for (i; i < ui->donot->topLevelItemCount(); i++)
	{
		QTreeWidgetItem *topItem = ui->donot->topLevelItem(i);
		if (topItem->text(0) == date)
		{
			currentDate = ui->donot->topLevelItem(i);
			break;
		}
	}
	if (i == ui->donot->topLevelItemCount())
	{
		currentDate = new QTreeWidgetItem(ui->donot);
		currentDate->setText(0, date);
		currentDate->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		currentDate->setFlags(currentDate->flags() & (~Qt::ItemIsEditable));
	}
	return currentDate;
}

QTreeWidgetItem *LabelMainWindow::_createDateInAl(QString date)
{
	int i = 0;
	QTreeWidgetItem *currentDate;

	for (i; i < ui->already->topLevelItemCount(); i++)
	{
		QTreeWidgetItem *topItem = ui->already->topLevelItem(i);
		if (topItem->text(0) == date)
		{
			currentDate = ui->already->topLevelItem(i);
			break;
		}
	}
	if (i == ui->already->topLevelItemCount())
	{
		currentDate = new QTreeWidgetItem(ui->already);
		currentDate->setText(0, date);
		currentDate->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		currentDate->setFlags(currentDate->flags() & (~Qt::ItemIsEditable));
	}
	return currentDate;
}

void LabelMainWindow::on_createnew_triggered()
{
    QStringList IDList;
    for(int i = 0; i < ui->donot->topLevelItemCount(); i++)
    {
		QTreeWidgetItem *childItem = ui->donot->topLevelItem(i);
		for(int j = 0; j < childItem->childCount(); j++)
		{
			IDList.push_back(childItem->child(j)->text(0));
		}
        
    }
    for(int i = 0; i < ui->already->topLevelItemCount(); i++)
    {
		QTreeWidgetItem *childItem = ui->already->topLevelItem(i);
		for (int j = 0; j < childItem->childCount(); j++)
		{
			IDList.push_back(childItem->child(j)->text(0));
		}
    }
    m_createNew = new CreateNew();
    m_createNew->show();
    m_createNew->IDList(IDList);
    connect(m_createNew, SIGNAL(createPatient(CreateNew *)), this, SLOT(createPatient(CreateNew *)));

}

void LabelMainWindow::createPatient(CreateNew *it)
{
	QDir *dir = new QDir;
	if (!dir->exists("./json/no/" + m_currentDate))
	{
		bool ok = dir->mkdir("./json/no/" + m_currentDate);
	}
	delete dir;
	_createDirByID("./json/no/" + m_currentDate + "/" + it->getPatientID(), it->getFileNameList());
    m_patientImageList.insert(it->getPatientID(), it->getFileNameList());
	m_IDflag.insert(it->getPatientID(), "no");

	QTreeWidgetItem *currentDate = _createDateInNO(m_currentDate);
	m_dateFromID.insert(it->getPatientID(), m_currentDate);

	QTreeWidgetItem* name = new QTreeWidgetItem(currentDate);
    name->setText(0, it->getPatientID());
	name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	name->setFlags(name->flags() & (~Qt::ItemIsEditable));
    _createPatient(it->getPatientID(), 0);
    ui->donot->setCurrentItem(name);
   // changePatient(name);

}

void LabelMainWindow::itemPressedSlot(QTreeWidgetItem * pressedItem,int index)
{
	if (NULL == pressedItem->parent())
		return;
    if(qApp->mouseButtons() == Qt::RightButton)   //判断是否为右键
    {
        QMenu *menu = new QMenu(ui->donot);
        menu->addAction(m_add);
       // menu->addAction(m_delete);
        menu->exec(QCursor::pos());//菜单弹出位置为鼠标点击位置
    }
}

void LabelMainWindow::treeItemChanged(QTreeWidgetItem *item, int column)
{
	if (ui->label_3->text() == NULL)
		return;
	//ImageInfo imageinfo = m_imageInfo.value(ui->label_3->text());
	//imageinfo.setState(true);
	//m_imageInfo.insert(ui->label_3->text(), imageinfo);
    if(item->parent() == NULL)
        return;

    if(Qt::Checked == item->checkState(0))
    {
		item->setBackgroundColor(0, QColor(90, 138, 224));
         QTreeWidgetItem* parent = item->parent();
		 if (item->parent()->text(0) == QStringLiteral("疾病"))
			 return;
         int count = parent->childCount(); //返回子项的个数
         {
             for(int i = 0; i < count; i++)
             {
                 if(parent->child(i)->checkState(0) == Qt::Checked && parent->child(i) != item)
                 {
                     parent->child(i)->setCheckState(0, Qt::Unchecked);
					 parent->child(i)->setBackgroundColor(0, QColor(255, 255, 255));
                 }
             }
         }
    }
	else
	{
		item->setBackgroundColor(0, QColor(255, 255, 255));
	}

}

void LabelMainWindow::on_LoadImage()
{
	QFileDialog fileDialog;
	QStringList list;
	fileDialog.setWindowTitle(QStringLiteral("选择图像"));
	fileDialog.setDirectory(tr("D:\\"));
	fileDialog.setNameFilter(tr("Images (*.png *.bmp *.jpg *.tif *.GIF *.dcm *jpeg))"));
	fileDialog.setFileMode(QFileDialog::ExistingFiles);
	if (fileDialog.exec() == QDialog::Accepted)
	{
		//strPathList  返回值是一个list，如果是单个文件选择的话，只要取出第一个来就行了。
		list = fileDialog.selectedFiles();
	}
    if(list.count( )<= 0)
    {
        QMessageBox::warning(this, tr("warning"), "choose no file!", QMessageBox::Yes);
        return ;
    }
	_createDirByID("./json/" + m_IDflag.value(ui->label_5->text()) + "/" + m_dateFromID.value(ui->label_5->text()) + "/" + ui->label_5->text(), list);
    QStringList patient = m_patientImageList.value(ui->donot->currentItem()->text(0));
    for(int i = 0; i < list.count(); i++)
    {
        if( !patient.contains(list.at(i).section('/', -1)))
        {
            patient.push_back(list.at(i).section('/', -1));
        }
    }
	
    m_patientImageList.insert(ui->donot->currentItem()->text(0), patient);

}

void LabelMainWindow::deletePatient()
{
    //QListWidgetItem *item = ui->donot->currentItem();
    //QMap<QString, QStringList>::iterator it = m_patientImageList.begin();
    //while(it != m_patientImageList.end())
    //{
    //    if(it.key() == item->text())
    //    {
    //        m_patientImageList.erase(it);
    //        break;
    //    }
    //    it++;
    //}
    //delete item;

}

void LabelMainWindow::showImage(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (m_isSaved == false)
	{
		QMessageBox::StandardButton button;
		button = QMessageBox::question(this, "",
			QString(QStringLiteral("警告：是否保存")),
			QMessageBox::Yes | QMessageBox::No);

		if (button == QMessageBox::Yes)
		{
			on_save_clicked();
		}
	}
	m_isSaved = true;

	_changeOneEyeLabel(1);
	int topCount = ui->focuslabel_1->topLevelItemCount();
	for (int i = 0; i < topCount; i++)
	{
		QTreeWidgetItem *item = ui->focuslabel_1->topLevelItem(0);
		_changeFocuslabel(item, 1);
	}
	m_checked.clear();
	m_OneEye.clear();
	m_disease.clear();
	if (current == NULL)
	{
		ui->paintLabel_L3->clean();
		ui->paintLabel_L3->cleanPainter();
		ui->paintLabel_L3->isNullImage(true);
		m_isNULLImage = true;
		_setLabelGeometry();
		ui->label_3->setText("");
		return;
	}

	ui->label_3->setText(current->text().section('/', -1));

    if(!m_imageInfo.contains(current->text().section('/', -1)))
    {
        ImageInfo imageinfo;
        m_OneLabelChecked.clear();

        if(m_isNULLImage == true)
        {
			ui->paintLabel_L3->BackImage(current->text());
			ui->paintLabel_L3->resize(ui->paintLabel_L3->size());
			m_origin = new QImage(ui->paintLabel_L3->OriPic());
            m_isNULLImage = false;
            ui->paintLabel_L3->isNullImage(false);
        }
		ui->paintLabel_L3->BackImage(current->text());
		ui->paintLabel_L3->resize(ui->paintLabel_L3->size());
		m_origin = new QImage(ui->paintLabel_L3->OriPic());
        ui->scrollArea_L1->widget()->setMinimumSize(ui->paintLabel_L3->size());
        ui->paintLabel_L3->setStep(1.0);
        ui->paintLabel_L3->setIndex(0);
		ui->paintLabel_L3->cleanPolyPool();
		_setLabelGeometry();
        imageinfo.setOrigin(*m_origin);
        m_imageInfo.insert(current->text().section('/', -1), imageinfo);
    }
    else
    {
        ImageInfo imageinfo = m_imageInfo.value(current->text().section('/', -1));
		if (imageinfo.getJsonFlag() == false)
		{
			_parseImg(imageinfo.getJsonValue(), m_IDflag.value(ui->label_5->text()), ui->label_5->text());
			imageinfo = m_imageInfo.value(current->text().section('/', -1));
		}
        if(m_isNULLImage == true)
        {
			ui->paintLabel_L3->BackImage(current->text());
			ui->paintLabel_L3->resize(ui->paintLabel_L3->size());
			m_origin = new QImage(ui->paintLabel_L3->OriPic());
			imageinfo.setOrigin(*m_origin);
			m_isNULLImage = false;
			ui->paintLabel_L3->isNullImage(false);
        }

        m_origin = imageinfo.getOrigin();
		ui->paintLabel_L3->BackImage(*m_origin);
		ui->paintLabel_L3->resize(ui->paintLabel_L3->size());
        ui->scrollArea_L1->widget()->setMinimumSize(ui->paintLabel_L3->size());
        ui->paintLabel_L3->setStep(imageinfo.getStep());
        ui->paintLabel_L3->setIndex(imageinfo.getIndex());
		ui->paintLabel_L3->cleanPolyPool();
		_setLabelGeometry();

		QMap<int, QPolygonF> tempMap = imageinfo.getPoly();
		QMap<int, QPolygonF>::Iterator it = tempMap.begin();

		while (it != tempMap.end())
		{
			QPolygonF temp = it.value();
			ui->paintLabel_L3->paint(temp, it.key());
			it++;
		}

		QMap<QString, QString> OneEye = imageinfo.getOneEye();
        QMap<QString, QString>::Iterator tempIt1 = OneEye.begin();
        while(tempIt1 != OneEye.end())
        {
             addOneEyeItem(tempIt1.key(), tempIt1.value());
             tempIt1++;
        }

		QList<QString> disease = imageinfo.getDisease();
		QList<QString>::iterator diseaseIt = disease.begin();
		while (diseaseIt != disease.end())
		{
			addDisease(*diseaseIt);
			diseaseIt++;
		}

		QMap<QString, QString> checked = imageinfo.getFocusInfo();
        QMap<QString, QString>::Iterator  tempIt2 = checked.begin();
        while(tempIt2 != checked.end())
        {
            _addLabel(tempIt2.key());
            addFocusItem(tempIt2.key(), tempIt2.value());
            tempIt2++;
        }
		m_imageInfo.insert(current->text().section('/', -1), imageinfo);
    }

}

void LabelMainWindow::addDisease(QString name)
{
	int topCount = ui->oneEye->topLevelItemCount();
	for (int i = 0; i < topCount; i++)
	{
		QTreeWidgetItem *item = ui->oneEye->topLevelItem(i);
		for (int j = 0; j < item->childCount(); j++)
		{
			if (item->text(0) == QStringLiteral("疾病") && item->child(j)->text(0) == name)
			{
				item->child(j)->setCheckState(0, Qt::Checked);
			}
		}
	}
}

void LabelMainWindow::addOneEyeItem(QString parent, QString child)
{

    int topCount = ui->oneEye->topLevelItemCount();
    for (int i = 0; i < topCount; i++)
    {
        QTreeWidgetItem *item = ui->oneEye->topLevelItem(i);
        for(int j = 0; j < item->childCount(); j++)
        {
           if(item->text(0) == parent && item->child(j)->text(0) == child)
           {
               item->child(j)->setCheckState(0,Qt::Checked);
           }
        }
    }
}

void LabelMainWindow::addFocusItem(QString parent, QString child)
{

    int topCount = ui->focuslabel_1->topLevelItemCount();
    for (int i = 0; i < topCount; i++)
    {
        QTreeWidgetItem *item = ui->focuslabel_1->topLevelItem(i);
        for(int j = 0; j < item->childCount(); j++)
        {
           if(item->text(0) == parent && item->child(j)->text(0) == child)
           {
               item->child(j)->setCheckState(0,Qt::Checked);
			   item->child(j)->setExpanded(true);
           }
        }
    }

}

void LabelMainWindow::changeSize(float size)
{
	ui->paintLabel_L3->resize(ui->paintLabel_L3->size());
	ui->scrollArea_L1->widget()->setMinimumSize(ui->paintLabel_L3->size());
	_setLabelGeometry();
}

void LabelMainWindow::treeAddLabel(int index)
{
    m_isSaved = false;
	//ImageInfo imageinfo = m_imageInfo.value(ui->label_3->text());
	//imageinfo.setState(true);
	//m_imageInfo.insert(ui->label_3->text(), imageinfo);
    char a[11];
    const char *p = itoa(index,a,10);
    QStringList rootName_1;
    rootName_1 << QObject::tr(p);
    QTreeWidgetItem *rootItem_1 = new QTreeWidgetItem(ui->focuslabel_1, rootName_1);

    QTreeWidgetItem* rootItem_1_1 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_1->setText(0,QStringLiteral("微动脉瘤(Microaneurysms)或者出血点(Hemorrhages Spot)"));  //设置子项显示的文本
    rootItem_1_1->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_2 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_2->setText(0,QStringLiteral("硬性渗出(Hard Exudate)"));  //设置子项显示的文本
    rootItem_1_2->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

	QTreeWidgetItem* rootItem_1_18 = new QTreeWidgetItem(rootItem_1);
	rootItem_1_18->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	rootItem_1_18->setText(0, QStringLiteral("微动脉瘤(Microaneurysms)"));  //设置子项显示的文本
	rootItem_1_18->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态


    QTreeWidgetItem* rootItem_1_3 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_3->setText(0,QStringLiteral("出血(Hemorrhages)"));  //设置子项显示的文本
    rootItem_1_3->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_4 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_4->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_4->setText(0,QStringLiteral("棉绒斑(Cotton Wool Spot)"));  //设置子项显示的文本
    rootItem_1_4->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_5 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_5->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_5->setText(0,QStringLiteral("静脉襻(Venous Loop)"));  //设置子项显示的文本
    rootItem_1_5->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_6 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_6->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_6->setText(0,QStringLiteral("墨渍样出血(Blot Hemorrhages)"));  //设置子项显示的文本
    rootItem_1_6->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_7 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_7->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_7->setText(0,QStringLiteral("静脉串珠(Venous Beading)"));  //设置子项显示的文本
    rootItem_1_7->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_8 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_8->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_8->setText(0,QStringLiteral("静脉复制(Venous Reproduction)"));  //设置子项显示的文本
    rootItem_1_8->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_9 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_9->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_9->setText(0,QStringLiteral("视网膜内微血管异常(IRMA - Intraretinal Microvascular Abnormities)"));  //设置子项显示的文本
    rootItem_1_9->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_10 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_10->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_10->setText(0,QStringLiteral("视网膜前出血(Pre Retinal Hemorrhages)"));  //设置子项显示的文本
    rootItem_1_10->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_11 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_11->setText(0,QStringLiteral("玻璃体出血(Vitreous Hemorrhages)"));  //设置子项显示的文本
    rootItem_1_11->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_12 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_12->setText(0,QStringLiteral("新生血管(New Vessels)"));  //设置子项显示的文本
    rootItem_1_12->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_13 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_13->setText(0,QStringLiteral("增殖膜(Fibrous Proliferation)"));  //设置子项显示的文本
    rootItem_1_13->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_14 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_14->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_14->setText(0,QStringLiteral("视盘(Optic Disk)"));  //设置子项显示的文本
    rootItem_1_14->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_15 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_15->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_15->setText(0,QStringLiteral("黄斑中央凹(Central Foveal Thickness)"));  //设置子项显示的文本
    rootItem_1_15->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* rootItem_1_16 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_16->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_16->setText(0,QStringLiteral("激光斑(Laser Spot)"));  //设置子项显示的文本
    rootItem_1_16->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态


    QTreeWidgetItem* rootItem_1_17 = new QTreeWidgetItem(rootItem_1);
    rootItem_1_17->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem_1_17->setText(0,QStringLiteral("other"));  //设置子项显示的文本
    rootItem_1_17->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态


	rootItem_1->setExpanded(true);
	for (int i = 0; i < ui->focuslabel_1->topLevelItemCount(); i++)
	{
		QTreeWidgetItem *item = ui->focuslabel_1->topLevelItem(i);
		if (item->text(0) == rootItem_1->text(0))
		{
			item->setExpanded(true);
		}
		else
		{
			item->setExpanded(false);
		}
	}
    ui->focuslabel_1->update();

}

void LabelMainWindow::setcurrentLabel(int index)
{

    char a[11];
    const char *p = itoa(index,a,10);
    QString temp = p;
    int topCount = ui->focuslabel_1->topLevelItemCount();
    for (int i = 0; i < topCount; i++)
    {
        QTreeWidgetItem *item = ui->focuslabel_1->topLevelItem(i);
		if (item->text(0) == temp)
		{
			ui->focuslabel_1->setCurrentItem(item);
			item->setBackgroundColor(0, QColor(90, 138, 224));
			item->setExpanded(true);
		}
		else
		{
			item->setBackgroundColor(0, QColor(255, 255, 255));
			item->setExpanded(false);
		}
    }

}

void LabelMainWindow::treeRemoveLabel(int index)
{
    m_isSaved = false;
    char a[11];
    const char *p = itoa(index,a,10);
    QString temp = p;
    int topCount = ui->focuslabel_1->topLevelItemCount();
    for (int i = 0; i < topCount; i++)
    {
        QTreeWidgetItem *item = ui->focuslabel_1->topLevelItem(i);
        if(item->text(0) == temp)
        {
            _del(item);
            ImageInfo imageinfo = m_imageInfo.value(ui->label_3->text());
            QMap<QString, QString> check = imageinfo.getFocusInfo();
            QMap<QString, QString>::Iterator it = check.begin();
            while(it != check.end())
            {
                if(it.key() == temp)
                {
                    check.erase(it);
                    break;
                }
                it++;
            }
            imageinfo.setFocusInfo(check);
			imageinfo.setPoly(ui->paintLabel_L3->labelInfo());
            m_imageInfo[ui->label_3->text()] = imageinfo;
            return;
        }
    }


}

void LabelMainWindow::changeNOPatient(QTreeWidgetItem *item, QTreeWidgetItem *previous)
{
	/*if (NULL == item->parent())
	{
		ui->label_7->setText(QString::number(item->childCount(), 10));
		return;
	}
	ui->label_7->setText(QString::number(item->parent()->childCount(), 10));

	_createPatient(item->text(0), 0);
	ui->label_5->setText(item->text(0));
	ui->listWidget->setCurrentItem(ui->listWidget->item(0));*/
}

void LabelMainWindow::changePatient(QTreeWidgetItem* item, int index)
{
	
	if (NULL == item->parent())
	{
		ui->label_7->setText(QString::number(item->childCount(), 10));
		return;
	}
	ui->label_7->setText(QString::number(item->parent()->childCount(), 10));


	if (m_isSaved == false)
	{
		QMessageBox::StandardButton button;
		button = QMessageBox::question(this, "",
			QString(QStringLiteral("警告：是否保存")),
			QMessageBox::Yes | QMessageBox::No);

		if (button == QMessageBox::Yes)
		{
			on_save_clicked();
		}
	}
	m_isSaved = true;
	_changeOneEyeLabel(1);
	int topCount = ui->focuslabel_1->topLevelItemCount();
	for (int i = 0; i < topCount; i++)
	{
		QTreeWidgetItem *item = ui->focuslabel_1->topLevelItem(0);
		_changeFocuslabel(item, 1);
	}
	m_checked.clear();
	m_OneEye.clear();

    _createPatient(item->text(0), 0);
	ui->label_5->setText(item->text(0));
	ui->listWidget->setCurrentItem(ui->listWidget->item(0));
  //  ui->donot->setCurrentItem(item);
}

void LabelMainWindow::changeALPatient(QTreeWidgetItem *item, int index)
{
	if (NULL == item->parent())
	{
		ui->label_7->setText(QString::number(item->childCount(), 10));
		return;
	}
	ui->label_7->setText(QString::number(item->parent()->childCount(), 10));


	if (m_isSaved == false)
	{
		QMessageBox::StandardButton button;
		button = QMessageBox::question(this, "",
			QString(QStringLiteral("警告：是否保存")),
			QMessageBox::Yes | QMessageBox::No);

		if (button == QMessageBox::Yes)
		{
			on_save_clicked();
		}
	}
	m_isSaved = true;
	_changeOneEyeLabel(1);
	int topCount = ui->focuslabel_1->topLevelItemCount();
	for (int i = 0; i < topCount; i++)
	{
		QTreeWidgetItem *item = ui->focuslabel_1->topLevelItem(0);
		_changeFocuslabel(item, 1);
	}
	m_checked.clear();
	m_OneEye.clear();

     _createPatient(item->text(0), 1);
	 ui->label_5->setText(item->text(0));
	 ui->listWidget->setCurrentItem(ui->listWidget->item(0));
     
}

void LabelMainWindow::LabelChanged(QTreeWidgetItem* item, int index)
{
	if (item->parent() != NULL)
		return;
	m_isSaved == false;
	for (int i = 0; i < ui->focuslabel_1->topLevelItemCount(); i++)
	{
		qDebug() << item->text(0);
		QTreeWidgetItem *child = ui->focuslabel_1->topLevelItem(i);
		child->setBackgroundColor(0, QColor(255, 255, 255));
	}
	item->setBackgroundColor(0, QColor(90, 138, 224));
}

void LabelMainWindow::showLabel(QTreeWidgetItem* item, int index)
{
	if (item->parent() != NULL)
		return;
	ui->paintLabel_L3->showLabel(item->text(0).toInt());

	int topCount = ui->focuslabel_1->topLevelItemCount();
	for (int i = 0; i < topCount; i++)
	{
		QTreeWidgetItem *child = ui->focuslabel_1->topLevelItem(i);
		child->setExpanded(false);
		if (item->text(0) == child->text(0))
		{
			item->setExpanded(true);
		}
	}

}

//qt点击事件
void LabelMainWindow::on_big_clicked()
{
    ui->paintLabel_L3->changeSize(1.1);
}

void LabelMainWindow::on_small_clicked()
{
    ui->paintLabel_L3->changeSize(0.9);
}

void LabelMainWindow::on_last_clicked()
{
   QListWidgetItem *item = ui->listWidget->currentItem();
   for(int i = 0; i < ui->listWidget->count() - 1; i++)
   {
       if(ui->listWidget->item(i+1)->text() == item->text())
       {
          ui->listWidget->setCurrentItem(ui->listWidget->item(i));
       }
   }
}

void LabelMainWindow::on_next_clicked()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(ui->listWidget->item(i)->text() == item->text() && i != ui->listWidget->count() - 1)
        {
            ui->listWidget->setCurrentItem(ui->listWidget->item(i+1));
        }
    }
}

void LabelMainWindow::on_load_triggered()
{
	m_checked.clear();
	m_OneEye.clear();
    QDir dir("./DataFromWeb");
    foreach(QFileInfo mfi ,dir.entryInfoList())
    {
        if(!mfi.isFile())
        {
            if(mfi.fileName()=="." || mfi.fileName() == "..")
                continue;
            _parseDir(mfi.absoluteFilePath());
        }
    }

}

void LabelMainWindow::on_save_clicked()
{
	m_checked.clear();
	m_OneEye.clear();
	m_disease.clear();
	m_isSaved = true;

	ImageInfo imageinfo = m_imageInfo.value(ui->label_3->text());
	_changeOneEyeLabel(0);
	int topCount = ui->focuslabel_1->topLevelItemCount();
	for (int i = 0; i < topCount; i++)
	{
		QTreeWidgetItem *item = ui->focuslabel_1->topLevelItem(i);
		_changeFocuslabel(item, 0);
	}
	ui->paintLabel_L3->changeSize(0.1);
	imageinfo.setPoly(ui->paintLabel_L3->labelInfo());
	imageinfo.setState(true);
	imageinfo.setStep(1.0);
	imageinfo.setIndex(ui->paintLabel_L3->getIndex());
	imageinfo.setDisease(m_disease);
	imageinfo.setOneEye(m_OneEye);
	imageinfo.setFocusInfo(m_checked);
	m_imageInfo[ui->label_3->text()] = imageinfo;
	m_OneEye.clear();
	m_checked.clear();
	m_disease.clear();

	_saveOneImg(m_IDflag.value(ui->label_5->text()), ui->label_5->text(), ui->label_3->text());
	QMessageBox::information(this, tr(" "), "save!");

	if (m_IDflag.value(ui->label_5->text()) == "yes")
		return;
	QStringList list = m_patientImageList[ui->label_5->text()];
	if (list.count() == 0)
		return;
	for (int i = 0; i < list.count(); i++)
	{
		ImageInfo info = m_imageInfo[list.at(i).section('/', -1)];
		if (info.getState() == false)
		{
			return;
		}
			
	}

	QString ID = ui->label_5->text();
	QString date = m_dateFromID.value(ID);
	for (int i = 0; i < ui->donot->topLevelItemCount(); i++)
	{
		QTreeWidgetItem *childItem = ui->donot->topLevelItem(i);
		for (int j = 0; j < childItem->childCount(); j++)
		{
			if (childItem->child(j)->text(0) == ID)
			{
				delete childItem->child(j);
				break;
			}
		}

	}
	m_IDflag.insert(ID, "yes");
	_moveNoToYes(ID);
	QTreeWidgetItem* currentDate = _createDateInAl(date);
	QTreeWidgetItem* name = new QTreeWidgetItem(currentDate);
	name->setText(0, ID);
	name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	name->setFlags(name->flags() & (~Qt::ItemIsEditable));
	
}


//qt事件
void LabelMainWindow::closeEvent(QCloseEvent *e)
{
	//if (m_isSaved == true)
	//{
	//	return;
	//}

	//QMessageBox::StandardButton button;
	//button = QMessageBox::question(this, QStringLiteral("退出程序"),
	//	QString(QStringLiteral("警告：是否保存并退出")),
	//	QMessageBox::Yes | QMessageBox::No | QMessageBox::Close);

	//if (button == QMessageBox::Close)
	//{
	//	e->ignore();
	//}
	//else if (button == QMessageBox::Yes)
	//{
	//	on_save_clicked();
	//	e->accept();//接受退出信号，程序退出
	//}
	//else if (button == QMessageBox::No)
	//{
	//	e->accept();//接受退出信号，程序退出
	//}

}


//网页数据处理函数
bool LabelMainWindow::removeFolderContent(const QString &folderDir)
{
	QDir dir(folderDir);
	QFileInfoList fileList;
	QFileInfo curFile;
	if (!dir.exists()) { return false; }//文件不存，则返回false
	fileList = dir.entryInfoList(QDir::Dirs | QDir::Files
		| QDir::Readable | QDir::Writable
		| QDir::Hidden | QDir::NoDotAndDotDot
		, QDir::Name);
	while (fileList.size() > 0)
	{
		int infoNum = fileList.size();
		for (int i = infoNum - 1; i >= 0; i--)
		{
			curFile = fileList[i];
			if (curFile.isFile())//如果是文件，删除文件
			{
				QFile fileTemp(curFile.filePath());
				fileTemp.remove();
				fileList.removeAt(i);
			}
			if (curFile.isDir())//如果是文件夹
			{
				QDir dirTemp(curFile.filePath());
				QFileInfoList fileList1 = dirTemp.entryInfoList(QDir::Dirs | QDir::Files
					| QDir::Readable | QDir::Writable
					| QDir::Hidden | QDir::NoDotAndDotDot
					, QDir::Name);
				if (fileList1.size() == 0)//下层没有文件或文件夹
				{
					dirTemp.rmdir(".");
					fileList.removeAt(i);
				}
				else//下层有文件夹或文件
				{
					for (int j = 0; j < fileList1.size(); j++)
					{
						if (!(fileList.contains(fileList1[j])))
							fileList.append(fileList1[j]);
					}
				}
			}
		}
	}
	return true;
}

void LabelMainWindow::_parseDir(QString path)
{

	QStringList patientImageList;
	if (!m_patientImageList.contains(path.section("/", -1)))
	{
		_differentID(patientImageList, path);
	}
	else
	{
		patientImageList = m_patientImageList.value(path.section("/", -1));
		_sameID(patientImageList, path);
	}
	
}

void LabelMainWindow::_differentID(QStringList patientImageList, QString path)
{
	QDir dir(path);
	QStringList list;
	QStringList movelist;
	foreach(QFileInfo mfi, dir.entryInfoList())
	{
		if (mfi.isFile() && mfi.fileName().section('.', -1) != "json")
		{
			if (!patientImageList.contains(mfi.absoluteFilePath().section('/', -1)))
			{
				movelist.push_back(mfi.absoluteFilePath());
				patientImageList.push_back(mfi.absoluteFilePath().section('/', -1));
			}
		}
		else
		{
			if (mfi.isFile() && mfi.fileName().section('.', -1) == "json")
			{
				_parseJsonFromWeb(mfi.absoluteFilePath(), path);
			}
		}
	}
	
	m_patientImageList.insert(path.section("/", -1), patientImageList);
	m_dateFromID.insert(path.section("/", -1), m_currentDate);

	

		int i = 0;
		for (i = 0; i < patientImageList.count(); i++)
		{
			ImageInfo info = m_imageInfo[patientImageList.at(i).section('/', -1)];
			if (info.getState() == false)
			{
				QTreeWidgetItem *currentDate = _createDateInNO(m_currentDate);
				QTreeWidgetItem* name = new QTreeWidgetItem(currentDate);
				name->setText(0, path.section("/", -1));
				name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				QDir exit;
				if (!exit.exists("./json/no/" + m_currentDate))
				{
					exit.mkdir("./json/no/" + m_currentDate);
				}
				name->setFlags(name->flags() & (~Qt::ItemIsEditable));
				_createDirByID("./json/no/" + m_currentDate + "/" + path.section("/", -1), movelist);
				m_IDflag.insert(path.section("/", -1), "no");
				for (int j = 0; j < patientImageList.count(); j++)
				{
					_saveOneImg("no", path.section("/", -1), patientImageList.at(j));
				}
				return;

			}
		}
		if (i == 0)
		{
			QTreeWidgetItem *currentDate = _createDateInNO(m_currentDate);
			QTreeWidgetItem* name = new QTreeWidgetItem(currentDate);
			name->setText(0, path.section("/", -1));
			name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QDir exit;
			if (!exit.exists("./json/no/" + m_currentDate))
			{
				exit.mkpath("./json/no/" + m_currentDate);
			}
			name->setFlags(name->flags() & (~Qt::ItemIsEditable));
			_createDirByID("./json/no/" + m_currentDate + "/" + path.section("/", -1), movelist);

			m_IDflag.insert(path.section("/", -1), "no");
			return;
		}
		if (i == patientImageList.count())
		{
			QTreeWidgetItem *currentDate = _createDateInAl(m_currentDate);
			QTreeWidgetItem* name = new QTreeWidgetItem(currentDate);
			name->setText(0, path.section("/", -1));
			name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QDir exit;
			if (!exit.exists("./json/yes/" + m_currentDate))
			{
				exit.mkpath("./json/yes/" + m_currentDate);
			}
			name->setFlags(name->flags() & (~Qt::ItemIsEditable));
			_createDirByID("./json/yes/" + m_currentDate + "/" + path.section("/", -1), movelist);
			m_IDflag.insert(path.section("/", -1), "yes");
			for (int j = 0; j < patientImageList.count(); j++)
			{
				_saveOneImg("yes", path.section("/", -1), patientImageList.at(j));
			}
			return;
		}
}

void LabelMainWindow::_sameID(QStringList patientImageList, QString path)
{
	if (patientImageList.count() == 0)
		return;
	QDir dir(path);
	QStringList list;
	QStringList movelist;
	int key = 0;
	QString firstImg;
	QString ID;
	foreach(QFileInfo mfi, dir.entryInfoList())
	{
		if (mfi.isFile() && mfi.fileName().section('.', -1) != "json")
		{
			if (key == 0)
			{
				firstImg = mfi.absoluteFilePath().section('/', -1);
				key++;
			}
			if (key == 1)
			{
				ID = _sameNum(firstImg, path.section('/', -1));//递归判断相同文件
				if (ID == NULL)
					return;
			}
			movelist.push_back(mfi.absoluteFilePath());
			list.push_back(mfi.absoluteFilePath().section('/', -1));
			
		}
		else
		{
			if (mfi.isFile() && mfi.fileName().section('.', -1) == "json")
			{
				_parseJsonFromWeb(mfi.absoluteFilePath(), path);
			}
		}
	}

	m_patientImageList.insert(ID, list);
	m_dateFromID.insert(ID, m_currentDate);

	int i = 0;
	for (i = 0; i < list.count(); i++)
	{
		ImageInfo info = m_imageInfo[list.at(i).section('/', -1)];
		if (info.getState() == false)
		{
			QTreeWidgetItem *currentDate = _createDateInNO(m_currentDate);
			QTreeWidgetItem* name = new QTreeWidgetItem(currentDate);
			name->setText(0, ID);
			name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			name->setFlags(name->flags() & (~Qt::ItemIsEditable));
			QDir exit;
			if (!exit.exists("./json/no/" + m_currentDate))
			{
				exit.mkpath("./json/no/" + m_currentDate);
			}
			_createDirByID("./json/no/" + m_currentDate + "/" + path.section("/", -1), movelist);
			m_IDflag.insert(ID, "no");
			for (int j = 0; j < patientImageList.count(); j++)
			{
				_saveOneImg("no", path.section("/", -1), patientImageList.at(j));
			}
			return;

		}
	}
	if (i == 0)
	{
		QTreeWidgetItem *currentDate = _createDateInNO(m_currentDate);
		QTreeWidgetItem* name = new QTreeWidgetItem(currentDate);
		name->setText(0, path.section("/", -1) + "_" + "1");
		name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		QDir exit;
		if (!exit.exists("./json/no/" + m_currentDate))
		{
			exit.mkpath("./json/no/" + m_currentDate);
		}
		name->setFlags(name->flags() & (~Qt::ItemIsEditable));
		_createDirByID("./json/no/" + m_currentDate + "/" + path.section("/", -1), movelist);
		m_IDflag.insert(ID, "no");
		return;
	}
	if (i == list.count())
	{
		QTreeWidgetItem *currentDate = _createDateInAl(m_currentDate);
		QTreeWidgetItem* name = new QTreeWidgetItem(currentDate);
		name->setText(0, path.section("/", -1) + "_" + "1");
		name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		name->setFlags(name->flags() & (~Qt::ItemIsEditable));
		QDir exit;
		if (!exit.exists("./json/yes/" + m_currentDate))
		{
			exit.mkpath("./json/yes/" + m_currentDate);
		}
		_createDirByID("./json/yes/" + m_currentDate + "/" + path.section("/", -1), movelist);
		m_IDflag.insert(ID, "yes");
		for (int j = 0; j < patientImageList.count(); j++)
		{
			_saveOneImg("yes", path.section("/", -1), patientImageList.at(j));
		}
		return;
	}
}

QString LabelMainWindow::_sameNum(QString imgPath, QString ID)
{
	
	QString IDTemp;
	static int i = 0;
	if (!m_patientImageList.contains(ID))
	{
		i = 0;
		return ID;
	}
	QStringList firstImg = m_patientImageList.value(ID);
	if (firstImg.contains(imgPath))
	{
		return NULL;
	}
	else
	{
		i++;
		return  IDTemp = _sameNum(imgPath, ID.section('(', 0, 0) + "(" + QString::number(i, 10) + ")");
	}

}

void LabelMainWindow::_parseJsonFromWeb(QString path, QString IDpath)
{
    QString val;
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    if (doc.isObject())
    {
        QJsonObject Tree = doc.object();
        QJsonObject::iterator TreeIt = Tree.begin();
        while(TreeIt != Tree.end())
        {
            _parseJson(TreeIt.value(), IDpath);
            TreeIt++;
        }

    }
}

void LabelMainWindow::_parseJson(QJsonValue root, QString path)
{
	PolygonContour polygonContour;
	QMap<int, QPolygonF> polyPool;
    QJsonObject childObj = root.toObject();
    QString imgName;
    imgName = childObj.value("filename").toString();
	QString allPath = path + "/" + imgName;
	cv::Mat mat = cv::imread(allPath.toStdString(), cv::IMREAD_GRAYSCALE);
	int height = mat.size().height;
	int width = mat.size().width;
    if(childObj.contains("image_labels"))
    {
        QJsonValue childvalue = childObj.value("image_labels");
        QJsonObject child2Obj = childvalue.toObject();
        QJsonObject::Iterator it;
        for(it = child2Obj.begin(); it != child2Obj.end(); it++)
        {
            //QJsonObject child3Obj = it.value().toObject();
            if(it.value() == "L1")
            {

            }
            else if(it.value() == "L1.L001")
            {
                m_OneEye.insert(QStringLiteral("眼别"), QStringLiteral("左眼"));
            }
            else if(it.value() == "L1.L002")
            {
                m_OneEye.insert(QStringLiteral("眼别"), QStringLiteral("右眼"));
            }
            else if(it.value() == "L2")
            {

            }
            else if(it.value() == "L2.L001")
            {
                m_OneEye.insert(QStringLiteral("图片质量"), QStringLiteral("清晰可见"));
            }
            else if(it.value() == "L2.L002")
            {
                m_OneEye.insert(QStringLiteral("图片质量"), QStringLiteral("可以评级"));
            }
            else if(it.value() == "L2.L003")
            {
                m_OneEye.insert(QStringLiteral("图片质量"), QStringLiteral("无法评级"));
            }
            else if(it.value() == "L3")
            {

            }
            else if(it.value() == "L3.L001")
            {
                m_OneEye.insert(QStringLiteral("图片位置"), QStringLiteral("黄斑为中心"));
            }
            else if(it.value() == "L3.L002")
            {
                m_OneEye.insert(QStringLiteral("图片位置"), QStringLiteral("视盘为中心"));
            }
            else if(it.value() == "L3.L003")
            {
                m_OneEye.insert(QStringLiteral("图片位置"), QStringLiteral("其他"));
            }
            else if(it.value() == "L4")
            {

            }
            else if(it.value() == "L4.L001")
            {

            }
            else if(it.value() == "L4.L001.L001")
            {
                m_OneEye.insert(QStringLiteral("糖网分期"), QStringLiteral("无视网膜病变"));
            }
            else if(it.value() == "L4.L001.L002")
            {
                m_OneEye.insert(QStringLiteral("糖网分期"), QStringLiteral("轻度非增值性糖尿病视网膜病变"));
            }
            else if(it.value() == "L4.L001.L003")
            {
                m_OneEye.insert(QStringLiteral("糖网分期"), QStringLiteral("中度非增值性糖尿病视网膜病变"));
            }
            else if(it.value()== "L4.L001.L004")
            {
                m_OneEye.insert(QStringLiteral("糖网分期"), QStringLiteral("重度非增值性糖尿病视网膜病变"));
            }
            else if(it.value() == "L4.L001.L005")
            {
                m_OneEye.insert(QStringLiteral("糖网分期"), QStringLiteral("增值性糖尿病视网膜病变"));
            }
            else if(it.value() == "L4.L002")
            {

            }
            else if(it.value() == "L4.L002.L001")
            {
               m_OneEye.insert(QStringLiteral("DME"), QStringLiteral("无明显的DME"));
            }
            else if(it.value() == "L4.L002.L002")
            {

            }
            else if(it.value() == "L4.L002.L002.L001")
            {
                m_OneEye.insert(QStringLiteral("DME"), QStringLiteral("轻度DME"));
            }
            else if(it.value() == "L4.L002.L002.L002")
            {
                m_OneEye.insert(QStringLiteral("DME"), QStringLiteral("中度DME"));
            }
            else if(it.value() == "L4.L002.L002.L003")
            {
               m_OneEye.insert(QStringLiteral("DME"), QStringLiteral("重度DME"));
            }

        }
    }
    if(childObj.contains("regions"))
    {
        QJsonValue childvalue = childObj.value("regions");
        QJsonObject child2Obj = childvalue.toObject();
        QJsonObject::Iterator it;
        for(it = child2Obj.begin(); it != child2Obj.end(); it++)
        {
            QJsonObject child3Obj = it.value().toObject();
            if(child3Obj.contains("shape_attributes"))
            {
				QJsonObject child4Obj = child3Obj.value("shape_attributes").toObject();
				if (child4Obj.value("name").toString() == "circle")
				{
					cv::Mat mask1 = cv::Mat(height, width, CV_8UC1, cv::Scalar(0));
					int x = child4Obj.value("cx").toInt();
					int y = child4Obj.value("cy").toInt();
					int r = child4Obj.value("r").toInt();
					cv::circle(mask1, cv::Point(x, y), r, cv::Scalar(255));
					polyPool.insert(it.key().toInt(), polygonContour.getPolygonContourFromWeb(mask1));

				}
				else if (child4Obj.value("name").toString() == "rect")
				{
					cv::Mat mask2 = cv::Mat(height, width, CV_8UC1, cv::Scalar(0));
					int x = child4Obj.value("x").toInt();
					int y = child4Obj.value("y").toInt();
					int w = child4Obj.value("width").toInt();
					int h = child4Obj.value("height").toInt();
					cv::rectangle(mask2, cv::Rect(x, y, w, h), cv::Scalar(255));
					polyPool.insert(it.key().toInt(), polygonContour.getPolygonContourFromWeb(mask2));

				}
				else if (child4Obj.value("name").toString() == "ellipse")
				{
					cv::Mat mask3 = cv::Mat(height, width, CV_8UC1, cv::Scalar(0));
					int x = child4Obj.value("cx").toInt();
					int y = child4Obj.value("cy").toInt();
					int rx = child4Obj.value("rx").toInt();
					int ry = child4Obj.value("ry").toInt();
					cv::ellipse(mask3, cv::Point(x, y), cv::Size(rx, ry), 0, 0, 360, cv::Scalar(255));
					polyPool.insert(it.key().toInt(), polygonContour.getPolygonContourFromWeb(mask3));

				}
				else if (child4Obj.value("name").toString() == "polygon")
				{
					cv::Mat mask4 = cv::Mat(height, width, CV_8UC1, cv::Scalar(0));
					QVector<int> vec_x;
					QVector<int> vec_y;
					QVector<QPoint> vec;
					QVariantList x = child4Obj.value("all_points_x").toArray().toVariantList();
					for (int i = 0; i < x.count(); i++)
					{
						vec_x.push_back(x.at(i).toInt());
					}
					QVariantList y = child4Obj.value("all_points_y").toArray().toVariantList();
					for (int i = 0; i < y.count(); i++)
					{
						vec_y.push_back(y.at(i).toInt());
					}
					for (int i = 0; i < vec_x.count(); i++)
					{
						vec.push_back(QPoint(vec_x.at(i), vec_y.at(i)));
					}
					QPolygon poly(vec);
					const int polygonSize = poly.size();
					cv::Point* oldPolygonPoints = new cv::Point[polygonSize];
					memset(oldPolygonPoints, 0, sizeof(cv::Point) * polygonSize);
					for (int i = 0; i < polygonSize; i++)
					{
						oldPolygonPoints[i].x = poly[i].x();
						oldPolygonPoints[i].y = poly[i].y();
					}
					const cv::Point* ppt[1] = { oldPolygonPoints };
					cv::fillPoly(mask4, ppt, &polygonSize, 1, cv::Scalar(255));
					polyPool.insert(it.key().toInt(), polygonContour.getPolygonContourFromWeb(mask4));

				}
				else if (child4Obj.value("name").toString() == "small_circle")
				{
					cv::Mat mask5 = cv::Mat(height, width, CV_8UC1, cv::Scalar(0));
					int x = child4Obj.value("cx").toInt();
					int y = child4Obj.value("cy").toInt();
					int r;
					if (width < 1000)
					{
						r = 20 * width / 1600 + 10;
					}
					else
					{
						r = 20 * width / 1600;
					}
					cv::circle(mask5, cv::Point(x, y), r, cv::Scalar(255), -1);
					polyPool.insert(it.key().toInt(), polygonContour.getPolygonContourFromWeb(mask5));

				}

				else if (child4Obj.value("name").toString() == "big_circle")
				{
					cv::Mat mask6 = cv::Mat(height, width, CV_8UC1, cv::Scalar(0));
					int x = child4Obj.value("cx").toInt();
					int y = child4Obj.value("cy").toInt();
					int r;
					if (width < 1000)
					{
						r = 80 * width / 1600 + 20;
					}
					else
					{
						r = 80 * width / 1600;
					}
					cv::circle(mask6, cv::Point(x, y), r, cv::Scalar(255), -1);
					polyPool.insert(it.key().toInt(), polygonContour.getPolygonContourFromWeb(mask6));
				}
				else
				{
				}



            }
            if(child3Obj.contains("region_attributes"))
            {
                QJsonObject child4value = child3Obj.value("region_attributes").toObject();
                if(child4value.contains("name"))
                {
                    m_checked.insert(it.key(), child4value.value("name").toString());
                }
            }
        }
    }

	qDebug() << polyPool;
	ImageInfo info = m_imageInfo.value(allPath.section('/', -1));
	info.setOneEye(m_OneEye);
	info.setFocusInfo(m_checked);
	info.setStep(1);
	info.setIndex(polyPool.count());
	info.setPoly(_resizePoint(polyPool, width));
	if (polyPool.count() != 0 || m_OneEye.count() != 0)
	{
		info.setState(true);
	}

	QString dcm = allPath.section(".", -1);
	if (dcm == "dcm")
	{
		QImage image(*Dcm2Image(allPath).getImage());
		ui->paintLabel_L3->BackImage(image);
	}
	else
	{
		ui->paintLabel_L3->BackImage(allPath);
	}
	m_origin = new QImage(ui->paintLabel_L3->OriPic());
	info.setOrigin(*m_origin);

	m_imageInfo.insert(allPath.section('/', -1), info);
	m_OneEye.clear();
	m_checked.clear();



	//QPixmap pixmap;
	//QString filepath = path + "/" + imgName;

	//QString dcm = filepath.section(".", -1);
	//if (dcm == "dcm")
	//{
	//	QImage image(*Dcm2Image(filepath).getImage());
	//	pixmap = QPixmap(QPixmap::fromImage(image));
	//}
	//else
	//{
	//	pixmap = QPixmap(filepath);
	//}
	//if (!pixmap.isNull())
	//{
	//	int width = pixmap.width();
	//	int height = pixmap.height();
	//	pixmap = pixmap.scaled(1000, height * 1000 / width);
	//	QPixmap origin(pixmap);
	//	info.setOrigin(origin);

	//	m_imageInfo.insert(filepath.section('/', -1), info);
	//}

}

QMap<int, QPolygonF> LabelMainWindow::_resizePoint(QMap<int, QPolygonF> polyPool, int width)
{
	float step = 1000.0 / (float)width ;

	QMap<int, QPolygonF>::Iterator it = polyPool.begin();
	while (it != polyPool.end())
	{
		QPolygonF temp = it.value();
		int count = temp.count();
		for (int i = 0; i < count; i++)
		{
			qDebug() << temp[i];
			temp[i] = QPointF(temp[i].x() * step, temp[i].y() * step);
		}
		polyPool[it.key()] = temp;
		it++;
		
	}
	return polyPool;
}
