#ifndef GETBILLCODE_H
#define GETBILLCODE_H

#include <QObject>
#include <QThread>
#include <QtNetwork/QNetworkCookieJar>
#include<QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QString>
#include <QJsonObject>
#include<QJsonDocument>
#include <httprequest.h>
#include <interfaceuser.h>
class getBillCode : public QThread
{
    Q_OBJECT
public:
    explicit getBillCode(QObject *parent = nullptr);
    void run();//线程入口

signals:

public slots:
    void userLoginInterfaceReply(QNetworkReply *reply);
    void getBillList();
private:
    QNetworkCookieJar *managerJar;
    QNetworkAccessManager *mainMangerNetwork;
    QString ipAddress;
    httpRequest HttpRequest;
    interfaceUser *InterFaceUser;
};

#endif // GETBILLCODE_H
