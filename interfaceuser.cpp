#include "interfaceuser.h"
#include <QObject>
#include <QDebug>
interfaceUser::interfaceUser(QObject *parent) : QThread(parent)
{
    managerJar = new QNetworkCookieJar(this);
    mainMangerNetwork = new QNetworkAccessManager(this);
    ipAddress = "http://211.157.179.73:9580";
    connect(this,SIGNAL(UserLoginDone(QString,QString)),this,SLOT(getBillList()));
}
/*
@brief:用户登录线程入口
@param:无
@return:无
@time:2019-10-17
*/
void interfaceUser::run()
{
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
                        if(object.contains("data"))
                        {
                            QJsonValue dataVal = object.value ("data");
                            if(dataVal.isObject ())
                            {
                                dataObject = dataVal.toObject ();
                                if(dataObject.contains ("name")){
                                    QJsonValue nameVal = dataObject.take ("name");
                                    name = nameVal.toString ();
                                    this->setRealName(name);
                                }
//                                emit UserLoginDone (this->getRealName(),this->getLoginMsg());
                            }
                        }

                    }
                }
           }
        }
        emit UserLoginDone (this->getRealName(),this->getLoginMsg());
    }
}
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
void interfaceUser::dealGetBillList(QNetworkReply *reply)
{
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
                for (int i =0;i<dataArray.size ();i++)
                {
                    QJsonValue billListVal = dataArray.at (i);
                    QJsonObject billListValObject = billListVal.toObject ();
                    QString code = billListValObject.value("code").toString();
                    QString billDate = billListValObject.value("billDate").toString();
                    QString moneyReim = billListValObject.value("moneyReim").toString();
                    QString use = billListValObject.value("use").toString();
                    this->setBillUse(use);
                    this->setBillCode(code);
                    this->setBillDate(billDate);
                    this->setBillMoney(moneyReim);
                }
            }

        }
    }
}
