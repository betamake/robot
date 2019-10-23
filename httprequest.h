#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QNetworkRequest>
/*
@brief:请求头封装类
@time:2019-10-17
*/
class httpRequest : public QObject
{
    Q_OBJECT
public:
    explicit httpRequest(QObject *parent = nullptr);
    QString getCurrentTime();
    QByteArray Image_To_Base64(QString ImgPath);
    QNetworkRequest getHttpRequest(QString url);
    QNetworkRequest getHttpRequestRemote(QString url);
signals:

public slots:
};

#endif // HTTPREQUEST_H
