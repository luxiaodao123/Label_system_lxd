#ifndef LABELMAINWINDOW_H
#define LABELMAINWINDOW_H

#include <QMainWindow>
#include "AccountManagement/mainaccountwindow.h"
#include "Patient/createnew.h"
#include "imageinfo.h"
#include <QMap>
#include <QStringList>
#include <QListWidgetItem>
#include <QTreeWidget>
#include <QJsonObject>
#include <QPolygonF>
#include <QJsonDocument>
#include <QCloseEvent>
#include "Base/process.h"
#include <QMultiMap>
#include <QMouseEvent>

namespace Ui {
class LabelMainWindow;
}

class LabelMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LabelMainWindow(QWidget *parent = 0);

    ~LabelMainWindow();

    void addFocusItem(QString parent, QString child);

    void addOneEyeItem(QString parent, QString child);

	void addDisease(QString name);

    bool removeFolderContent(const QString &folderDir);

protected:
    void closeEvent(QCloseEvent *e);

	//void resizeEvent(QResizeEvent *e);

private:
    void _initOneEye();

	void _initLabelWindow();

	void _setLabelGeometry();

    void _createPatient(QString ID, int flag);

    void _quitAndSave(QString ID, QString Date, int flag);

	void _saveOneImg(QString flag, QString ID, QString imgName);

    void _saveImageInfo(QJsonObject *jsonObject, QString imagename);

    void _loadDir(QString path, int flag);

    void _parse(QString path, QString ID, QString flag);

	void _differentID(QStringList patientImageList, QString path);

	void _sameID(QStringList patientImageList, QString path);

    void _parseImg(QJsonValue childObj, QString flag, QString ID);

    void _parseDir(QString path);

    void _parseJsonFromWeb(QString path, QString IDpath);

    void _parseJson(QJsonValue childObj, QString path);

    void _changeOneEyeLabel(int flag);
    
    void _changeFocuslabel(QTreeWidgetItem* node, int flag);

    void _del(QTreeWidgetItem* node);

    void _addLabel(QString str);

	void _loadNo(QString ID, QTreeWidgetItem *item);
	
	void _loadYes(QString ID, QTreeWidgetItem *item);

	void _loadJsonNo(QString path);

	void _loadJsonYes(QString path);

	void _createDirByID(QString path, QStringList list);

	void _moveNoToYes(QString ID);

	QMap<int, QPolygonF> _resizePoint(QMap<int, QPolygonF>, int);

	QString _sameNum(QString, QString);

	QString _getDate();

	QTreeWidgetItem *_createDateInNO(QString date);

	QTreeWidgetItem *_createDateInAl(QString date);


private slots:
  //  void on_AccountManagement_triggered();

    void on_createnew_triggered();

    void createPatient(CreateNew *it);

    void showImage(QListWidgetItem *, QListWidgetItem *);

    void changeNOPatient(QTreeWidgetItem*, QTreeWidgetItem*);

    void changeALPatient(QTreeWidgetItem* ,int);

    void changePatient(QTreeWidgetItem*, int);

    void itemPressedSlot(QTreeWidgetItem *, int);

    void treeItemChanged(QTreeWidgetItem *, int);

	void LabelChanged(QTreeWidgetItem*, int);

	void showLabel(QTreeWidgetItem*, int);

    void on_LoadImage();

    void deletePatient();

    void changeSize(float size);

    void treeAddLabel(int index);

    void setcurrentLabel(int index);

    void treeRemoveLabel(int index);

    void on_big_clicked();

    void on_small_clicked();

    void on_save_clicked();

    void on_last_clicked();

    void on_next_clicked();

    void on_load_triggered();


private:
    Ui::LabelMainWindow *ui;
   // MainAccountWindow *m_mainAccountWindow;
    CreateNew *m_createNew;
    QMap<QString, QStringList> m_patientImageList;
	QMap<QString, QString> m_IDflag;
    QMap<QString, ImageInfo> m_imageInfo;
    QMap<QString, QString> m_checked;
	QList<QString> m_disease;
    QMap<QString, QMap<QString, QString>> m_OneLabelChecked;
	QMap<QString, QString> m_dateFromID;
    QMap<QString, QString> m_OneEye;
    QMap<QString, QJsonObject> m_jsonMap;
    int m_currentIndex;
    QPixmap *m_pixmap;
    QImage *m_origin;
	QPixmap *m_white;
    QAction *m_add;
    QAction *m_delete;
    bool m_isNULLImage;
    bool m_isSaved;
	QString m_currentDate;
	
	QPointF m_PosStart;//起始点
	QPointF m_Poscurrent;//当前点
	QVector<QPointF> m_PointPool;//存放坐标
	QMap<int, QPolygonF> m_polyPool;

};

#endif // LABELMAINWINDOW_H

