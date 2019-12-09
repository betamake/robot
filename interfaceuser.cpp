#if _MSC_VER >= 1600	// MSVC2015 > 1899,	MSVC_VER = 14.0
#pragma execution_character_set("utf-8")
#endif
#include "interfaceuser.h"
#include <QObject>
#include <QDebug>
interfaceUser *interfaceUser::instance =NULL;
interfaceUser::interfaceUser(QObject *parent) : QObject(parent)
{
    list.clear();
    ipAddress = "http://211.157.179.73:9720";
}
interfaceUser::~interfaceUser(){
    delete instance;
    instance = NULL;
}
interfaceUser *interfaceUser::getinstance ()
{
    if (NULL == instance) {
        instance = new interfaceUser();
    }
    return instance;
}
/*
@brief:用户登录线程入口
@param:无
@return:无
@time:2019-10-17
*/
void interfaceUser::userLogin()
{
    qDebug()<<"password:"<<interfaceUser::getinstance()->getPassword();
    qDebug()<<"username:"<<interfaceUser::getinstance()->getUsername();
    managerJar = new QNetworkCookieJar();
    mainMangerNetwork = new QNetworkAccessManager();
    connect(mainMangerNetwork,SIGNAL(finished(QNetworkReply *)),this,SLOT(userLoginInterfaceReply(QNetworkReply *)));
    QJsonObject loginJsonObject;
    loginJsonObject.insert ("password",this->getPassword());
    loginJsonObject.insert ("username",this->getUsername());
    QJsonDocument document;
    document.setObject (loginJsonObject);
    QByteArray loginArray = document.toJson (QJsonDocument::Compact);
    QNetworkRequest request = HttpRequest.getHttpRequestRemote(ipAddress.left(26).append("/10gin"));
    QNetworkReply *reply = mainMangerNetwork->post (request,loginArray);
    mainMangerNetwork->setCookieJar (managerJar);

}
/*
@brief:处理用户返回的信息，并且成功之后发送处理信号。信号由票据接口和主程序端跳转使用。
@param:无
@return:无
@time:2019-10-17
*/
void interfaceUser::userLoginInterfaceReply(QNetworkReply *reply)
{
    qDebug()<<"进入槽函数";
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray all = reply->readAll();
        QJsonParseError jsonError;
        QJsonObject dataObject;
        QString name;
        qint16 msg;
        QJsonDocument doucment = QJsonDocument::fromJson(all, &jsonError);
        qDebug()<< QString(doucment.toJson()).replace("\n","").replace("\"","").replace(" ","")<<endl;
        if((!doucment.isEmpty()) && jsonError.error == QJsonParseError::NoError)
        {
            if(doucment.isObject())
            {
                QJsonObject object = doucment.object();
                if(object.contains ("code"))
                {
                    QJsonValue dataVal = object.take("code");
                    msg = dataVal.toInt();
                    this->setLoginMsg(msg);

                    if (msg == 0)
                    {
                            QJsonValue dataVal = object.value ("data");
                            dataObject = dataVal.toObject ();
                            QJsonValue userVal = dataObject.value("user");
                            QJsonObject userObject = userVal.toObject();
                            if(userObject.contains ("name")){
                            QJsonValue nameVal = userObject.take ("name");
                            name = nameVal.toString ();
                            this->setRealName(name);

                        }
                    }
                    emit UserLoginDone (this->getRealName(),this->getLoginMsg());
                }


           }
        }


        //因为获取票据列表的时候会进入这里，先在这里断开登录连接测试代码
        disconnect(mainMangerNetwork,SIGNAL(finished(QNetworkReply *)),this,SLOT(userLoginInterfaceReply(QNetworkReply *)));
    }
}
/*
@brief:获取报销单单据号列表
@param:无
@return:无
@time:2019-10-17
*/
void interfaceUser::getBillList()
{
    connect(mainMangerNetwork,SIGNAL(finished(QNetworkReply *)),this,SLOT(dealGetBillList(QNetworkReply *)));
    QUrlQuery params;
    params.addQueryItem("billType",this->getBillType());
    QString  data = params.toString();
    QNetworkRequest request = HttpRequest.getHttpRequestRemote
            (ipAddress.left(26).append("/reim/robot/billList?").append (data.toUtf8()));
    request.setHeader(QNetworkRequest::ContentLengthHeader, data.size());
    mainMangerNetwork->setCookieJar (managerJar);
    QNetworkReply *reply = mainMangerNetwork->get (request);

}
/*
@brief:处理报销单据号接口函数
@param:无
@return:无
@time:2019-10-17
*/
void interfaceUser::dealGetBillList(QNetworkReply *reply)
{
    qDebug() << "-----------------------getBillList"<<reply->error();
    list.clear();

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray all = reply->readAll();
        QJsonParseError jsonError;
        QJsonObject dataObject;
        QJsonDocument doucment = QJsonDocument::fromJson(all, &jsonError);
        qDebug()<< QString(doucment.toJson()).replace("\n","").replace("\"","").replace(" ","")<<endl;
        if((!doucment.isEmpty()) && jsonError.error == QJsonParseError::NoError)
        {
            QJsonObject object = doucment.object();
            QJsonValue dataVal = object.take("msg");
            QString msg = dataVal.toString ();
            //获得总金额字段
            QString accountLabel = getAccountLabel();
            QString useLabel = getUseLabel();
            if (msg=="操作成功")
            {
                QJsonValue dataVal  = object.value ("data");
                QJsonArray dataArray = dataVal.toArray ();
                qDebug() << "count = " << dataArray.size();
                for (int i =0;i<dataArray.size ();i++)
                {
                    QJsonValue billListVal = dataArray.at (i);
                    QJsonObject billListValObject = billListVal.toObject ();
                    QString code = billListValObject.value("code").toString();
                    QString billDate = billListValObject.value("billDate").toString();
                    //金额保留两位小数
                    QString moneyReim =QString::number(billListValObject.value(accountLabel).toDouble(), 'f', 2) ;
                    QString use = billListValObject.value(useLabel).toString();

                    billInfo info;
                    info.billUse = use;
                    info.billCode = code;
                    info.billDate = billDate;
                    info.billMoney = moneyReim;
                    insertBillInfo(info);
                }
                emit sentDealBillListDone ();
            }

        }
    }

    disconnect(mainMangerNetwork,SIGNAL(finished(QNetworkReply *)),this,SLOT(dealGetBillList(QNetworkReply *)));
}
/**
 * @brief 获得总金额字段
 * @return
 */
QString interfaceUser::getAccountLabel()
{
    QString account = "moneyReim";

    QString billType = this->getBillType();
    if (billType == "FY")
        account = "moneyReim";
    else if (billType == "CL")
        account = "moneyReim";
    else if (billType == "CG")
        account = "moneyReim";
    else if (billType == "QK")
        account = "moneyLoan";
    else if (billType == "HK")
        account = "money";
    else if (billType == "ZZ")
        account = "moneyTransferOut";
    else if (billType == "LY")
        account = "money";
    else if (billType == "ZS")
        account = "money";

    return account;
}
/**
 * @brief 获得摘要字段
 * @return
 */
QString interfaceUser::getUseLabel()
{
    QString account = "use";

    QString billType = this->getBillType();
    if (billType == "FY")
        account = "use";
    else if (billType == "CL")
        account = "use";
    else if (billType == "CG")
        account = "use";
    else if (billType == "QK")
        account = "use";
    else if (billType == "HK")
        account = "summary";
    else if (billType == "ZZ")
        account = "summary";
    else if (billType == "LY")
        account = "summary";
    else if (billType == "ZS")
        account = "summary";

    return account;
}
/*
@brief:获取报销单单据号列表
@param:无
@return:无
@time:2019-10-17
*/
void interfaceUser::getbillAttachment()
{
    QNetworkAccessManager *billMangerNetwork = new QNetworkAccessManager(this);
    connect(billMangerNetwork,SIGNAL(finished(QNetworkReply *)),this,SLOT(dealbillAttachment(QNetworkReply *)));
    QUrlQuery params;
    params.addQueryItem("billCode",this->getBillCode());
    QString  data = params.toString();
    QNetworkRequest request = HttpRequest.getHttpRequestRemote
            (ipAddress.left(26).append("/reim/robot/billAttachment?").append (data.toUtf8()));
    request.setHeader(QNetworkRequest::ContentLengthHeader, data.size());
    billMangerNetwork->setCookieJar (managerJar);
    QNetworkReply *reply = billMangerNetwork->get (request);

}
void interfaceUser::dealbillAttachment(QNetworkReply *reply)
{
    qDebug() << "-----------------------getBillList\n" << reply->error();
    aList.clear();

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray all = reply->readAll();
        QJsonParseError jsonError;
        QJsonObject dataObject;
        QJsonDocument doucment = QJsonDocument::fromJson(all, &jsonError);
        qDebug()<< QString(doucment.toJson()).replace("\n","").replace("\"","").replace(" ","")<<endl;
        if((!doucment.isEmpty()) && jsonError.error == QJsonParseError::NoError)
        {
            QJsonObject object = doucment.object();
            QJsonValue dataVal = object.take("msg");
            QString msg = dataVal.toString ();
            if (msg=="操作成功")
            {
                QJsonValue dataVal  = object.value ("data");
                QJsonArray dataArray = dataVal.toArray ();
                qDebug() << "count = " << dataArray.size();
                this->setBillNum(dataArray.size ());//记录票据的数量
                for (int i =0;i<dataArray.size ();i++)
                {
                    QJsonValue billListVal = dataArray.at (i);
                    QJsonObject billListValObject = billListVal.toObject ();
                    QString attachmentId = billListValObject.value("id").toString();
                    QString attachmentName = billListValObject.value("name").toString();
                    QString attachmentPath =billListValObject.value("path").toString() ;
                    QString attachmentType = billListValObject.value("type").toString();        //发票、其他
                    QString invoiceType = billListValObject.value("invoiceType").toString();    //0纸质发票，1电子发票

                    attachment info;
                    info.attachmentId = attachmentId;
                    info.attachmentName = attachmentName;
                    info.attachmentPath = attachmentPath;
                    info.attachmentType = attachmentType;
                    info.invoiceType = invoiceType;
                    insertAttachmentInfo(info);
                }
                emit sentDealAttachmentDone();
            }
        }
    }
}
void interfaceUser::saveList()
{
    managerJar = new QNetworkCookieJar();
    mainMangerNetwork = new QNetworkAccessManager();
    connect(mainMangerNetwork,SIGNAL(finished(QNetworkReply *)),this,SLOT(userLoginInterfaceReply(QNetworkReply *)));
    QJsonObject loginJsonObject;
    loginJsonObject = documentJson.buildJsonObject();
//    loginJsonObject.insert ("password",this->getPassword());
//    loginJsonObject.insert ("username",this->getUsername());
    QJsonDocument document;
    document.setObject (loginJsonObject);
    QByteArray loginArray = document.toJson (QJsonDocument::Compact);
    QNetworkRequest request = HttpRequest.getHttpRequestRemote(ipAddress.left(26).append("/10gin"));
    QNetworkReply *reply = mainMangerNetwork->post (request,loginArray);
    mainMangerNetwork->setCookieJar (managerJar);
}
QByteArray interfaceUser::InitGetRequest(QString url,QString obj)
{
    //循环拼接
    QString baseUrl =url;
    //构造请求
    QNetworkRequest request;
    request.setUrl(QUrl(baseUrl));
    QNetworkAccessManager *pictureManager = new QNetworkAccessManager();
    // 发送请求
    QNetworkReply *pReplay = pictureManager->get(request);
//    pictureManager->setCookieJar(managerJar);
    //开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(pReplay,SIGNAL(finished()), &eventLoop, SLOT(quit()));

    //add timeout deal
    QTimer *tmpTimer = new QTimer();
    connect(tmpTimer,SIGNAL(timeout()),&eventLoop, SLOT(quit()));
    tmpTimer->setSingleShot(true);
    tmpTimer->start(5000);
    eventLoop.exec();
    tmpTimer->stop();

    if (pReplay->error() == QNetworkReply::NoError)
    {
        qInfo() << QString("request %1 NoError").arg(obj);
    }
    else
    {
        qWarning()<<QString("request %1 handle errors here").arg(obj);
        QVariant statusCodeV = pReplay->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        //statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
        qWarning()<<QString("request %1 found error ....code: %2 %3").arg(obj).arg(statusCodeV.toInt()).arg((int)pReplay->error());
        qWarning(qPrintable(pReplay->errorString()));
    }
    //获取响应信息
    QByteArray bytes = pReplay->readAll();
    return bytes;
}

