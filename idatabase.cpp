#include "idatabase.h"
#include <QCoreApplication> // 确保包含
#include <QDir>             // 确保包含
#include <QDebug>
#include <QUuid>
#include <QSqlRecord>
#include <QSqlField>



void IDatabase::ininDatabase()
{
    // 1. 获取应用程序的运行路径
    QString appDirPath = QCoreApplication::applicationDirPath();
    qDebug() << appDirPath;

    // 2. 拼接数据库文件的完整路径
    QString aFile = QDir::toNativeSeparators(appDirPath + "/lab4a.db");
    qDebug() << aFile;


    // 4. 尝试连接数据库
    database = QSqlDatabase::addDatabase("QSQLITE"); // 再次确认拼写
    database.setDatabaseName(aFile);

    if (!database.open()) {
        // 5. 如果失败，打印最关键的错误信息
        qDebug() << "failed";
        qDebug() << "failed_reson" << database.lastError().text();
    } else {
        qDebug() << "success";
    }
    qDebug() << "99";
}

bool IDatabase::initPatientModel()
{
    PatienttabModel = new QSqlTableModel(this, database);
    PatienttabModel->setTable("patient");
    PatienttabModel->setEditStrategy(
        QSqlTableModel::OnManualSubmit); // 数据保存方式，OnManualSubmit ，OnRowChange
    PatienttabModel->setSort(PatienttabModel->fieldIndex("name"), Qt::AscendingOrder); // 排序
    if (!(PatienttabModel->select())) // 查询!
        return false;

    thePatientSelection = new QItemSelectionModel(PatienttabModel);
    return true;
}

int IDatabase::addNewPatient()
{
    PatienttabModel->insertRow(PatienttabModel->rowCount(), QModelIndex()); // 在末尾添加一个记录
    QModelIndex curIndex = PatienttabModel->index(PatienttabModel->rowCount() - 1, 1); // 创建最后一行的ModelIndex

    int curRecNo = curIndex.row();
    QSqlRecord curRec = PatienttabModel->record(curRecNo); // 获取当前记录
    curRec.setValue("CREATEDTIMESTAMP", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));
    PatienttabModel->setRecord(curRecNo, curRec);

    return curIndex.row();
}

bool IDatabase::searchPatient(QString filter)
{
    PatienttabModel->setFilter(filter);
    return PatienttabModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();
    PatienttabModel->removeRow(curIndex.row());
    PatienttabModel->submitAll();
    PatienttabModel->select();

}

bool IDatabase::submitPatientEdit()
{
    return PatienttabModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
    PatienttabModel->revertAll();
}



QString IDatabase::userLogin(QString userName, QString password)
{
    //  return "loginOK";
    QSqlQuery query;
    query.prepare("select username, password from user where username = :USER");
    query.bindValue(":USER", userName);
    query.exec();
    qDebug() << query.lastQuery() << query.first();
    if (query.first() && query.value("username").isValid()) {
        QString passwd = query.value("password").toString();
        if (passwd == password) {
            qDebug() << "login ok";
            return "loginOk";
        } else {
            qDebug() << "wrong password";
            return "wrongPassword";
        }
    } else {
        qDebug() << "no such user";
        return "wrongUsername";
    }
}






IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    ininDatabase();
}
