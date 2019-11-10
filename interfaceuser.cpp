#include "interfaceuser.h"
#include <QObject>
#include <QDebug>
interfaceUser *interfaceUser::instance =NULL;
interfaceUser::interfaceUser(QObject *parent) : QObject(parent)
{
    list.clear();
    ipAddress = "http://211.157.179.73:9580";
//    211.157.179.73:9580/admin/review/view?path=2019/11/04/3f104f448329b00a.txt
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
        QString msg;
        QJsonDocument doucment = QJsonDocument::fromJson(all, &jsonError);
        qDebug()<< QString(doucment.toJson()).replace("\n","").replace("\"","").replace(" ","")<<endl;
        if((!doucment.isEmpty()) && jsonError.error == QJsonParseError::NoError)
        {
            if(doucment.isObject())
            {
                QJsonObject object = doucment.object();
                if(object.contains ("msg"))
                {
                    QJsonValue dataVal = object.take("msg");
                    msg = dataVal.toString ();
                    this->setLoginMsg(msg);
                    if (msg =="登录成功")
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
                }
           }
        }
        emit UserLoginDone (this->getRealName(),this->getLoginMsg());

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
    qDebug() << "-----------------------getBillList";
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
                    QString moneyReim =QString::number(billListValObject.value("moneyReim").toInt()) ;
                    QString use = billListValObject.value("use").toString();

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
/*
@brief:获取报销单单据号列表
@param:无
@return:无
@time:2019-10-17
*/
void interfaceUser::getbillAttachment()
{
    connect(mainMangerNetwork,SIGNAL(finished(QNetworkReply *)),this,SLOT(dealGetBillList(QNetworkReply *)));
    QUrlQuery params;
    params.addQueryItem("billCode",this->getBillCode());
    QString  data = params.toString();
    QNetworkRequest request = HttpRequest.getHttpRequestRemote
            (ipAddress.left(26).append("/reim/robot/billAttachment?").append (data.toUtf8()));
    request.setHeader(QNetworkRequest::ContentLengthHeader, data.size());
    mainMangerNetwork->setCookieJar (managerJar);
    QNetworkReply *reply = mainMangerNetwork->get (request);

}
void interfaceUser::dealbillAttachment(QNetworkReply *reply)
{
    qDebug() << "-----------------------getBillList";
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
                    QString attachmentId = billListValObject.value("invoiceNum").toString();
                    QString attachmentName = billListValObject.value("billDate").toString();
                    QString attachmentPath =billListValObject.value("path").toString() ;
                    QString attachmentType = billListValObject.value("type").toString();
                    QString invoiceType = billListValObject.value("invoiceType").toString();

                    attachment info;
                    info.attachmentId = attachmentId;
                    info.attachmentName = attachmentName;
                    info.attachmentPath = attachmentPath;
                    info.attachmentType = attachmentType;
                    info.invoiceType = invoiceType;
                    insertAttachmentInfo(info);
                }
            }
        }
    }
}
