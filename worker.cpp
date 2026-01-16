#include "worker.h"
#include "idatabase.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <QJsonArray>  // <--- 添加这一行
#include <QDebug>
#include <qjsonobject.h>


Worker::Worker(QObject *parent) : QObject(parent) {}

void Worker::batchImportData(const QJsonArray &data)
{
    QSqlDatabase db = IDatabase::getInstance().getDatabase();
    if (!db.transaction()) {
        emit workFinished(false, "无法开启数据库事务");
        return;
    }

    QSqlQuery query(db);
    bool hasError = false;

    // 模拟循环插入 1000 条数据
    for (const QJsonValue &value : data) {
        QJsonObject obj = value.toObject();
        // 假设数据结构
        QString name = obj["class_name"].toString();
        QString room = obj["room_number"].toString();

        query.prepare("INSERT INTO class_room (class_name, room_number) VALUES (?, ?)");
        query.addBindValue(name);
        query.addBindValue(room);

        if (!query.exec()) {
            qDebug() << "Insert error:" << query.lastError().text();
            hasError = true;
            break;
        }

        // 模拟耗时，演示线程效果
        QThread::msleep(5);
    }

    if (hasError) {
        db.rollback();
        emit workFinished(false, "数据导入失败，已回滚");
    } else {
        db.commit();
        emit workFinished(true, "数据导入成功");
    }
}

void Worker::exportBigFile(const QString &content, const QString &path)
{
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // 模拟大文件写入的耗时
        QThread::msleep(1000);
        QTextStream out(&file);
        out << content;
        file.close();
        emit workFinished(true, "文件导出成功");
    } else {
        emit workFinished(false, "无法打开文件");
    }
}
