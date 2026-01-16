#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QSqlError>
#include <QDataWidgetMapper>

class IDatabase : public QObject
{
    Q_OBJECT

public:
    // 获取单例实例
    static IDatabase &getInstance()
    {
        static IDatabase instance;
        return instance;
    }

    // === 【新增】解决 mainwindow 报错的关键函数 ===
    // 提供对私有 database 变量的只读访问
    QSqlDatabase getDatabase() {
        return database;
    }

    // 数据库连接状态查询
    bool isOpen() const;
    QString getLastError() const;

    // 用户登录
    QString userLogin(QString userName, QString password); // 修正了参数名 pasword -> password

    // === 病人信息相关操作 ===
    bool initPatientModel();
    int addNewPatient();
    bool searchPatient(QString filter);
    bool deleteCurrentPatient();
    bool submitPatientEdit();
    void revertPatientEdit();

    // 公有成员变量（用于界面绑定）
    QSqlTableModel *PatienttabModel;
    QItemSelectionModel *thePatientSelection;

signals:
    void databaseConnected();
    void databaseError(const QString &error);

private:
    // 私有构造函数（单例模式）
    explicit IDatabase(QObject *parent = nullptr);

    // 禁用拷贝构造和赋值运算符
    IDatabase(const IDatabase &) = delete;
    IDatabase &operator=(const IDatabase &) = delete;

    // === 私有成员变量 ===
    QSqlDatabase database;
    QString lastError;

    // === 私有内部函数 ===
    void ininDatabase(); // 初始化数据库连接（内部调用）
};

#endif // IDATABASE_H
