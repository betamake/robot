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
class BillIdentify : public QThread
{
    Q_OBJECT
public:
    explicit BillIdentify(QObject *parent = nullptr);
    void run();
signals:

public slots:
    void billReply(QNetworkReply *reply);
private:
    QFileDialog *fileDialog;
    QString billpath;
    QNetworkAccessManager *manager;
    httpRequest HttpRequest;
    QString address;
};

#endif // BILLIDENTIFY_H
