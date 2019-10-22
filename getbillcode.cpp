#include "getbillcode.h"

getBillCode::getBillCode(QObject *parent) : QThread(parent)
{
    managerJar = new QNetworkCookieJar(this);
    mainMangerNetwork = new QNetworkAccessManager(this);
    InterFaceUser = new interfaceUser(this);
    ipAddress = "http://211.157.179.73:9580";
}
void getBillCode::run()
{
    connect(mainMangerNetwork,SIGNAL(finished(QNetworkReply *)),this,SLOT(userLoginInterfaceReply(QNetworkReply *)));
    QJsonObject loginJsonObject;
    loginJsonObject.insert ("password",InterFaceUser->getPassword());
    loginJsonObject.insert ("username",InterFaceUser->getUsername());
    QJsonDocument document;
    document.setObject (loginJsonObject);
    QByteArray loginArray = document.toJson (QJsonDocument::Compact);
    QNetworkRequest request = HttpRequest.getHttpRequestRemote(ipAddress.left(26).append("/10gin"));
    QNetworkReply *reply = mainMangerNetwork->post (request,loginArray);
    mainMangerNetwork->setCookieJar (managerJar);
}
void getBillCode::userLoginInterfaceReply(QNetworkReply *reply)
{

}
