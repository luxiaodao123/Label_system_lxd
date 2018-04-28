#ifndef CREATENEW_H
#define CREATENEW_H

#include <QWidget>

namespace Ui {
class CreateNew;
}

class CreateNew : public QWidget
{
    Q_OBJECT

public:
    explicit CreateNew(QWidget *parent = 0);

    CreateNew(const CreateNew &temp);

    ~CreateNew();

    const QStringList getFileNameList() const;

    const QString getPatientID() const;

    void initImageList(QString fileName);

    void IDList(QStringList list);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void createPatient(CreateNew *it);

private:
    Ui::CreateNew *ui;
    QStringList m_fileNameList;
    QList<QString> m_FilesList;
    QString m_patientID;
    QStringList m_IDList;
};

#endif // CREATENEW_H
