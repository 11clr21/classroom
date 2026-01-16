#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QVariantList>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

public slots:
    // 任务1：批量插入数据到数据库 (耗时操作)
    void batchImportData(const QJsonArray &dataToSave);

    // 任务2：大文件导出 (耗时操作)
    void exportBigFile(const QString &content, const QString &path);

signals:
    // 任务完成信号
    void workFinished(bool success, const QString &message);
};

#endif // WORKER_H
