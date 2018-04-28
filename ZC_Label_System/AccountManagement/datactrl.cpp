#include "datactrl.h"

DataCtrl::DataCtrl() : m_iQSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))
{
   m_iQSqlDatabase.setDatabaseName("sqlite.dat");
   m_iQSqlDatabase.open();
   QSqlQuery("create table if not exists sqlite (usr TEXT primary key, pwd TEXT)", m_iQSqlDatabase).exec();
//   if(!DataCtrl::verify("admin", QCryptographicHash::hash(QString("admin").toLocal8Bit(), QCryptographicHash::Md5).toHex()))
//   {
//       qDebug() << "in";
//        DataCtrl::usrReg("admin", QCryptographicHash::hash(QString("admin").toLocal8Bit(), QCryptographicHash::Md5).toHex());
//   }
   if(!DataCtrl::verify("admin", "admin"))
   {
       qDebug() << "in";
        DataCtrl::usrReg("admin", "admin");
   }

}

DataCtrl::~DataCtrl()
{
    m_iQSqlDatabase.commit();
    m_iQSqlDatabase.close();
}

bool DataCtrl::verify(const QString &strName, const QString &strPwd)
{
    QSqlQuery query(QString("select * from sqlite where usr = '%1' and pwd ='%2'").arg(strName, strPwd), m_iQSqlDatabase);
    query.exec();
	return query.next();

}


bool DataCtrl::usrReg(const QString &strName, const QString &strPwd)
{
    QSqlQuery query(QString("replace into sqlite (usr, pwd) values('%1', '%2')").arg(strName, strPwd), m_iQSqlDatabase);
    return query.exec();
}

bool DataCtrl::del(const QString &strName)
{
    QSqlQuery query(QString("delete from sqlite where usr = '%1'").arg(strName), m_iQSqlDatabase);
    return query.exec();
}

