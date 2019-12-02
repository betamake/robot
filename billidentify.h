#ifndef BILLIDENTIFY_H
#define BILLIDENTIFY_H

#include <QObject>
#include <QThread>
#include <QFileDialog>
#include <QFile>
#include<QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QString>
#include <QJsonObject>
#include<QJsonDocument>
#include <httprequest.h>
#include <QUrlQuery>
#include <QJsonArray>
#include <QStringList>
#include <QCoreApplication>
class BillIdentify : public QThread
{
    Q_OBJECT
public:
    explicit BillIdentify(QObject *parent = nullptr);
//    QByteArray getPixmapData(QString filePath,QImage image);
    void run();
signals:
    void success();
public slots:
    void billReply(QNetworkReply *reply);
private:
    QFileDialog *fileDialog;
    QString billpath;
    QNetworkAccessManager *manager;
    httpRequest HttpRequest;
    QString address;
    //票据相关
    QString regFilePath;
    QString uname;
    QString billdir;
    QStringList bldir;
    QStringList blpath;
    QString picName;//保存的图片名称
    QString billname;//票据附件名
    //发票
    QString billCode; //参考票据识别接口
    QString billNumber;
    QString fbillDate;
    QString billGoods;
    QString billPrice;
    QString billCheckcode;
    int costRowcount;
    bool costType;
    // 火车票相关
    QString trainPerson;//参照火车票返回接口
    QString trainDate;
    QString trainStart;
    QString trainPrice;
    QString trainEnd;
    int busiRowcount;
    bool busiType;
    //飞机票相关
    bool abroadType;
    int abroadRowcount;
};

#endif // BILLIDENTIFY_H
