#ifndef QRDECODE_H
#define QRDECODE_H

#include <QObject>
#include <QHttpMultiPart>
#include <QCameraImageCapture>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QList>
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QUrlQuery>
#include "httprequest.h"
#include <QByteArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QDir>
#include <QPixmap>
#include <QJsonArray>
#include <QFile>
#include <QObject>
#include <QList>
#include <QCoreApplication>
#include "interfaceuser.h"
#include <QHttpPart>
/*
@brief:识别二维码
@time:2019-10-17
*/
class QrInformation
{
public:
    QString getBillCode()
    {
        return this->billCode;
    }
    void setBillCode(const QString billCode)
    {
        this->billCode = billCode;
    }
    QCameraViewfinder *getviewfinder()
    {
        return this->viewfinder;
    }
    void setviewfinder(QCameraViewfinder *viewfinder)
    {
        this->viewfinder=viewfinder;
    }
    QCameraImageCapture *getimageCapture(){
        return this->imageCapture;
    }
    void setimageCapture(QCameraImageCapture *imageCapture){
        this->imageCapture=imageCapture;
    }
    QCamera *getcamera(){
        return this->camera;
    }
    void setcamera(QCamera *camera){
        this->camera=camera;
    }
private:
    QString billCode;
    QCameraViewfinder *viewfinder;
    QCameraImageCapture *imageCapture;
    QCamera *camera;

};

class QrDecode : public QThread
{
    Q_OBJECT
public:
    explicit QrDecode(QObject *parent = nullptr);
    ~QrDecode();
    QrInformation getQrInfo(){
        return QrInfo;
    }
    QrInformation QrInfo;
    static QrDecode *getinstance();
    QString getPixmapData(QString filePath,QImage image);
    void run();

    void initCamera();
signals:
    void qrCheckFailure();
    void qrDone( QString billCode);

public slots:
    void QrCheck();
    void sendPhoto(int Id, QImage image);
    void qrReply(QNetworkReply *reply);
//    void qrDone();
private:
    static QrDecode *instance;
    int currentIndex;
    int facetime;
    QTimer *timer;
    int sentIndex;
    int idFace;
    bool isFaceOk;
    QString address;
    httpRequest HttpRequest;
};

#endif // QRDECODE_H
