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
#include "documentjson.h"
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
    QString invoiceType;
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
    QString getAccountLabel();
    QString getUseLabel();
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
    int getBillNum()
    {
        return this->billNum;
    }
    void setBillNum(const int billNum)
    {
        this->billNum = billNum;
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
    void insertAttachmentInfo(attachment& info){
        QList<attachment>::iterator i;
        for(i=aList.begin(); i!=aList.end(); i++){
            if (i->attachmentId == info.attachmentId)
                break;
        }
        if (i==aList.end())
            aList.insert(i, info);
    }

    QList<attachment> getAttachment(){
        return aList;
    }

    static interfaceUser *getinstance();
    void getBillList();
    void getbillAttachment();
    void saveList();

signals:
    void UserLoginDone(QString realName,QString loginMsg);
    void sentDealBillListDone();
    void sentDealAttachmentDone();

public slots:
        void userLoginInterfaceReply(QNetworkReply *reply);
        void dealGetBillList(QNetworkReply *reply);
        void dealbillAttachment(QNetworkReply *reply);

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
    int billNum;

    billInfoList list;
    attachmentList aList;
    DocumentJson documentJson;
};

#endif // INTERFACEUSER_H
