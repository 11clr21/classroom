#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

    // 请求班级列表
    void fetchClassList();
    // 请求公告
    void fetchNotices(const QString &date);

signals:
    // 信号：当获取到班级数据时发射
    void classListDataReceived(const QJsonArray &dataArray);
    // 信号：当获取到公告数据时发射
    void noticeDataReceived(const QString &noticeTitle);
    // 信号：网络错误
    void errorOccurred(const QString &errorString);

private slots:
    void onClassListReply(QNetworkReply *reply);
    void onNoticeReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
};

#endif // NETWORKMANAGER_H
