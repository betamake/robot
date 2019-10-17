#include "interfaceuser.h"
#include <QObject>
#include <QDebug>
interfaceUser::interfaceUser(QObject *parent) : QThread(parent)
{
    managerJar = new QNetworkCookieJar(this);
    mainMangerNetwork = new QNetworkAccessManager(this);
    ipAddress = "http://211.157.179.73:9580";
}
/*
@brief:用户登录线程入口
@param:无
@return:无
@time:2019-10-17
*/
void interfaceUser::run()
{
    connect(mainMangerNetwork,SIGNAL(finished(QNetworkReply *)),this,SLOT(userLoginInterfaceReply(QNetworkReply *reply)));
    QJsonObject loginJsonObject;
    loginJsonObject.insert ("password",this->getPassword());
    loginJsonObject.insert ("username",this->getUsername());
    QJsonDocument document;
    document.setObject (loginJsonObject);
    QByteArray loginArray = document.toJson (QJsonDocument::Compact);
    QNetworkRequest request = HttpRequest.getHttpRequestRemote(ipAddress.left(26).append("/1ogin"));
    QNetworkReply *reply = mainMangerNetwork->post (request,loginArray);
    mainMangerNetwork->setCookieJar (managerJar);

}
/*
@brief:处理用户返回的信息
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
                    if (msg =="登陆成功")
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
                                    emit UserLoginDone (this->getRealName(),this->getLoginMsg());
                            }
                        }

                    }
                }
           }
        }
    }

}
