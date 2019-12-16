#include "qrdecode.h"
QrDecode *QrDecode::instance =NULL;
QrDecode::QrDecode(QObject *parent) : QThread(parent)
{
    address = "http://211.157.179.73:9720/admin/qrcode/resolve?";
//    address = "http://192.168.1.208:9000/admin/attachment/pro/upload?";
    this->initCamera ();

}
QrDecode::~QrDecode(){
    delete instance;
    instance = NULL;
}
QrDecode *QrDecode::getinstance ()
{
    if (NULL == instance) {
        instance = new QrDecode();
    }
    return instance;
}
/*
@brief:摄像头初始化
@param:无
@return:无
@time:2019-10-30
*/
void QrDecode::initCamera ()
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    if(cameras.count() > 0){
        foreach (const QCameraInfo &cameraInfo, cameras) {
            qDebug()<<cameraInfo.description();
        }
        QCamera *camera = new QCamera(cameras.at(1));
        QrInfo.setcamera (camera);
    }
    //登录
    QCameraViewfinder *viewfinder = new QCameraViewfinder();
    QrInfo.setviewfinder (viewfinder);
    QrInfo.getcamera ()->setViewfinder( QrInfo.getviewfinder ());
    QrInfo.getviewfinder ()->resize(800,800);

    QCameraImageCapture *imageCapture = new QCameraImageCapture(QrInfo.getcamera ());
    QrInfo.setimageCapture (imageCapture);

    QrInfo.getcamera ()->setCaptureMode(QCamera::CaptureStillImage);
    QrInfo.getimageCapture ()->setCaptureDestination(QCameraImageCapture::CaptureToFile);
}
/*
@brief:用户登录线程入口
@param:无
@return:无
@time:2019-10-30
*/
void QrDecode::run ()
{
    isFaceOk = false;
    //扫描二维码次数
    facetime = 0;


    qDebug()<<"进入线程";
    timer = new QTimer(this);
    timer->setInterval(2000);//1s发送一次timeout信号
    connect(timer, SIGNAL(timeout()), this, SLOT(QrCheck()));
    timer->start();//启动定时器
    exec() ;
}
/*
@brief:图片编码
@param:filePath：图片路径，image：图片编码
@return:无
@time:2019-10-30
*/
QString QrDecode::getPixmapData(QString filePath,QImage image)
{
    //    qDebug()<<"发送照片";
    QString baseDir = QCoreApplication::applicationDirPath();
    QString fileDir = baseDir.append(filePath);

    //创建目录
    QDir dir;
    if(!dir.exists(fileDir))
    {
        bool res = dir.mkpath(fileDir);
        qDebug() << "创建二维码目录结果:" << res;
    }

//    fileDir.append(HttpRequest.getCurrentTime());
    fileDir.append(".jpg");

    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap.save(fileDir);
    qDebug()<<fileDir<<endl;

    return fileDir;
}
/*
@brief:二维码检测
@param:无
@return:无
@time:2019-10-30
*/
void QrDecode::QrCheck ()
{
    if(QCamera::ActiveStatus == QrInfo.getcamera ()->status())
    {
//        qDebug()<<"第" << facetime << "次查询二维码";
        facetime++;
        idFace = 2;
        QrInfo.getimageCapture ()->capture();
        //take photos
        if(facetime < 4)
        {
            connect(QrInfo.getimageCapture (), SIGNAL(imageCaptured(int,QImage)), this, SLOT(sendPhoto(int,QImage)));
        }else
        {
            qDebug() << "qr check failed, stop send photos"<< endl;
            if(timer->isActive ())
            {
                timer->stop ();
            }
            QrInfo.getcamera ()->stop ();
            emit qrCheckFailure ();
        }

    }
}
/*
@brief:给后端发送二维码信息
@param:image：图片编码
@return:reply:接口返回的信息
@time:2019-10-30
*/
void QrDecode::sendPhoto (int Id, QImage image)
{
    if(idFace == 2 && !isFaceOk)
    {
        QString fileDir = this->getPixmapData("/files/qr_file",image);
//        QFile file(fileDir);

//        if (!file.open(QIODevice::ReadOnly)||file.size()==0)
//        {
//            file.close();
//            qDebug() << "文件打开失败";
//        }
//        QByteArray fdata = file.readAll();
//        file.close();


        QNetworkAccessManager *manager  = new QNetworkAccessManager(this);
        QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(qrReply(QNetworkReply*)));
        //封装请求参数(看接口文档)
//通过QHttpMultiPart实现。测试无法通过
        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart imagePart;
        imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"file\";filename=\"qr_file.jpg\"")));
        QFile *file = new QFile(fileDir);
        file->open(QIODevice::ReadOnly);
        imagePart.setBodyDevice(file);
        file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
        multiPart->append(imagePart);
        //请求地址
        QUrl url(address);
        QNetworkRequest request(url);
        QNetworkReply *reply = manager->post(request,multiPart);
        multiPart->setParent(reply);
    }
}
void QrDecode::qrReply(QNetworkReply *reply)
{
    qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).value<int>();
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray all = reply->readAll();
        QJsonParseError jsonError;
        QJsonObject dataObject;
        QString billCode;
        QJsonDocument doucment = QJsonDocument::fromJson(all, &jsonError);
        qDebug()<< QString(doucment.toJson()).replace("\n","").replace("\"","").replace(" ","")<<endl;
        if((!doucment.isEmpty()) && jsonError.error == QJsonParseError::NoError)
        {
            if(doucment.isObject())
            {
                QJsonObject object = doucment.object();
                QJsonValue dataVal = object.value ("data");
                 billCode = dataVal.toString ();
                 QrInfo.setBillCode(billCode);
                 interfaceUser::getinstance()->setBillCode(billCode);
                 emit qrDone();

           }
        }
    }
}
