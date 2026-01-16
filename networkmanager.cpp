#include "networkmanager.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>


NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
}


void NetworkManager::fetchClassList()
{
    // 模拟请求地址，实际替换为你的服务器 API
    QUrl url("http://your-api.com/api/classes");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onClassListReply(reply);
    });
}


void NetworkManager::fetchNotices(const QString &date)
{
    // 模拟带参数的请求
    QUrl url(QString("http://your-api.com/api/notices?date=%1").arg(date));
    QNetworkRequest request(url);

    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onNoticeReply(reply);
    });
}


void NetworkManager::onClassListReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) {
            emit classListDataReceived(doc.array());
        }
    } else {
        emit errorOccurred(reply->errorString());
    }
    reply->deleteLater();
}


void NetworkManager::onNoticeReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        // 假设返回格式是 {"title": "xxx"}
        if (doc.isObject()) {
            QString title = doc.object().value("title").toString();
            emit noticeDataReceived(title);
        }
    } else {
        emit errorOccurred(reply->errorString());
    }
    reply->deleteLater();
}
