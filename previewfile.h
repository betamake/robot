#ifndef PREVIEWFILE_H
#define PREVIEWFILE_H

#include <QtNetwork/QNetworkCookieJar>
#include<QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QThread>
#include <QObject>
#include <QString>
#include <QJsonObject>
#include<QJsonDocument>
#include <httprequest.h>
#include <QUrlQuery>
#include <QJsonArray>
#include <interfaceuser.h>
class PreviewFile : public QThread
{
    Q_OBJECT
public:
    explicit PreviewFile(QObject *parent = nullptr);
    void run();
    QString getpath(){
        return this->path;
    }
    void setpath(const QString path)
    {
        this->path = path;
    }

signals:

public slots:
private:
        QNetworkAccessManager *mainMangerNetwork;
        QString ipAddress;
        httpRequest HttpRequest;
        QString path;
};

#endif // PREVIEWFILE_H
