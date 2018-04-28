#ifndef DATACTRL_H
#define DATACTRL_H

#include <QtGui>
#include <QtSql/QSqlDatabase>
#include <QtCore>
#include <QtSql/QSqlQuery>

class DataCtrl : public QObject
{

public:

    DataCtrl();
    ~DataCtrl();
    bool verify(const QString &strName, const QString &strPwd);
    bool usrReg(const QString &strName, const QString &strPwd);
    bool del(const QString &strName);

private:

    QSqlDatabase m_iQSqlDatabase;
};

#endif // DATACTRL_H
