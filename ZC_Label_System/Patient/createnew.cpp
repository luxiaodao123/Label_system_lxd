#include "createnew.h"
#include "ui_createnew.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidget>

CreateNew::CreateNew(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateNew)
{
    ui->setupUi(this);
	QIcon  *logo = new QIcon("./Resources/logo.ico");
	this->setWindowIcon(*logo);
    this->setWindowTitle(QStringLiteral("新建"));
    ui->label_2->setStyleSheet("color:red;");
}

CreateNew::CreateNew(const CreateNew &temp)
{
    m_patientID = temp.getPatientID();
    m_fileNameList = temp.getFileNameList();
}

CreateNew::~CreateNew()
{
    delete ui;
}

void CreateNew::on_pushButton_clicked()
{
    QString ID = ui->lineEdit->text();
    if(ID.isNull())
        return;
    m_patientID = ID;
    QFileDialog fileDialog;
    fileDialog.setWindowTitle(QStringLiteral("选择图像"));
    fileDialog.setDirectory(tr("D:\\"));
    fileDialog.setNameFilter(tr("Images (*.png *.bmp *.jpg *.tif *.GIF *.dcm *.jpeg))"));
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    if (fileDialog.exec() == QDialog::Accepted)
    {
        m_fileNameList = fileDialog.selectedFiles();
		if (m_fileNameList.count() <= 0)
		{
			QMessageBox::warning(this, tr("warning"), "choose no file!", QMessageBox::Yes);
			return;
		}
    }
    
    for(int i = 0; i < m_fileNameList.count(); i++)
    {
        if(!m_FilesList.contains(m_fileNameList[i]))
        {
            m_FilesList.append(m_fileNameList[i]);
			initImageList(m_fileNameList[i]);
        }
    }
}

void CreateNew::on_pushButton_2_clicked()
{
    QString ID = ui->lineEdit->text();
    if(ID.isEmpty())
    {
        ui->label_2->setText(QStringLiteral("ID为空"));
        return;
    }
    m_patientID = ID;
    if(m_IDList.contains(ID))
    {
        ui->label_2->setText(QStringLiteral("已存在"));
        return;
    }
    emit createPatient(this);
    this->close();
}

const QStringList CreateNew::getFileNameList() const
{
    return m_fileNameList;
}

const QString CreateNew::getPatientID() const
{
    return m_patientID;
}

void CreateNew::initImageList(QString fileName)
{

    QListWidgetItem* image = new QListWidgetItem(ui->listWidget);
    image->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    image->setText(fileName.section("/", -1));  //设置子项显示的文本
 //   m_imgPath.insert(fileName.section("/", -1), fileName);

}

void CreateNew::IDList(QStringList list)
{
    m_IDList = list;
}
