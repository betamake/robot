#ifndef INTERFACEUSER_H
#define INTERFACEUSER_H
#include <QtNetwork/QNetworkCookieJar>
#include<QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QThread>
#include <QObject>
#include <QString>
#include <QJsonObject>
#include<QJsonDocument>
#include <httprequest.h>
#include <QUrlQuery>
#include <QJsonArray>
/*
@brief:后端接口类
@time:2019-10-17
*/

//票据和票据列表结构
typedef struct{
    QString billCode;
    QString billDate;
    QString billMoney;
    QString billUse;
} billInfo;

typedef QList<billInfo> billInfoList;

//附件和附件列表结构
typedef struct{
    QString attachmentId;
    QString attachmentName;
    QString attachmentPath;
    QString attachmentType;
} attachment;

typedef QList<attachment> attachmentList;

class interfaceUser : public QObject
{
    Q_OBJECT
public:
    explicit interfaceUser(QObject *parent = nullptr);
    ~interfaceUser();
    void userLogin();
    //用户名密码
    QString getUsername(){
        return this->username;
    }
    void setUsername(const QString username){
        this->username = username;
    }
    QString getPassword(){
        return this->password;
    }
    void setPassword(const QString password){
        this->password=password;
    }
    //login返回的信息
    QString getRealName(){
        return this->realName;
    }
    void setRealName(const QString realName){
        this->realName=realName;
    }
    QString getLoginMsg(){
        return this->loginMsg;
    }
    void setLoginMsg(const QString loginMsg){
        this->loginMsg = loginMsg;
    }
    QString getBillType(){
        return this->billType;
    }
    void setBillType(const QString billType){
        this->billType = billType;
    }
    QString getBillCode(){
        return this->billCode;
    }
    void setBillCode(const QString billCode)
    {
        this->billCode = billCode;
    }
    QString getBillDate(){
        return this->billDate;
    }
    void setBillDate(const QString billDate){
        this->billDate = billDate;
    }
    QString getBillMoney(){
        return this->billMoney;
    }
    void setBillMoney(const QString billMoney)
    {
        this->billMoney = billMoney;
    }
    QString getBillUse(){
        return this->billUse;
    }
    void setBillUse(const QString billUse){
        this->billUse = billUse;
    }

    void insertBillInfo(billInfo& bill){
        QList<billInfo>::iterator i;
        for(i=list.begin(); i!=list.end(); i++){
            if (i->billCode == bill.billCode)
                break;
        }
        if (i==list.end())
            list.insert(i, bill);
    }

    QList<billInfo> getList(){
        return list;
    }

    static interfaceUser *getinstance();

signals:
    void UserLoginDone(QString realName,QString loginMsg);
    void sentDealBillListDone();
public slots:
        void userLoginInterfaceReply(QNetworkReply *reply);
        void getBillList();
        void dealGetBillList(QNetworkReply *reply);

private:
     static interfaceUser *instance;
    //用户名密码
    QString username;
    QString password;
    //login返回的信息
    QString realName;
    QString loginMsg;
    //管理请求的cookie
    QNetworkCookieJar *managerJar;
    QNetworkAccessManager *mainMangerNetwork;
    QString ipAddress;
    httpRequest HttpRequest;
    //
    QString billType;
    QString billCode;
    QString billDate;
    QString billMoney;
    QString billUse;

    billInfoList list;
};

#endif // INTERFACEUSER_H
