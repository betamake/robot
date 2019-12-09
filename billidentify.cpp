//#pragma execution_character_set(“utf-8”)
#include "billidentify.h"

BillIdentify::BillIdentify(QObject *parent) : QThread(parent)
{
    address = "http://192.168.3.185:8000";
}

void BillIdentify::run()
{
//    QString runpath= QCoreApplication::applicationDirPath();
    QString scanBillpath="C:/Users/betamake/Documents/scan.jpg";

    qDebug() << "fileName:" << scanBillpath;
    manager = new QNetworkAccessManager(this);
    //读取完成后识别票据
    QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(billReply(QNetworkReply*)));
    QFile file(scanBillpath);
    if (!file.open(QIODevice::ReadOnly)||file.size()==0)
    {
        file.close();
        return ;
    }
    QByteArray fdata = file.readAll();
    file.close();
    fdata = fdata.toBase64();
    fdata = fdata.replace("+","-");
    fdata = fdata.replace("/","_");
    QUrlQuery params;
    params.addQueryItem("image",fdata);
    params.addQueryItem("imageType",".jpg");
    QString  data = params.toString();
    QNetworkRequest request = HttpRequest.getHttpRequest(address.left(25).append("/bill/"));
    request.setHeader(QNetworkRequest::ContentLengthHeader, data.size());
    manager->post(request,params.toString().toUtf8());
    exec();
}
/**
* @brief       票据识别返回处理
* @author        胡帅成
* @date        2018-09-06
*/
void BillIdentify::billReply(QNetworkReply * reply){
    //打印结果
    qDebug() << "------票据识别结果------"<<reply->error()<< endl;
    if(reply->error() ==    QNetworkReply::NoError){
        QByteArray all = reply->readAll();
        QJsonParseError jsonError;
        QJsonDocument doucment = QJsonDocument::fromJson(all, &jsonError);  // 转化为 JSON 文档
        if((!doucment.isEmpty()) && jsonError.error == QJsonParseError::NoError){//解析未发生错误
            if(doucment.isObject()){
                QJsonObject object = doucment.object();
                if(object.contains("success")){
                    int success = 0;
                    QJsonValue successVal = object.value("success");
                    if(successVal.isDouble()){
                        success = successVal.toInt();
                    }
                    if(success == 1){
                        int billType = 0;
                        if(object.contains("type")){
                            QJsonValue typeVal = object.value("type");
                            if(typeVal.isDouble()){
                                billType = typeVal.toInt();
                            }
                        }
                        QJsonObject infoObj;
                        if(object.contains("info")){
                            QJsonValue infoVal = object.value("info");
                            if(infoVal.isObject()){
                                infoObj = infoVal.toObject();
                            }
                        }
                        QString type;
                        QString billContent;
                        QString user;
                        QString start;
                        QString end;
                        QString billDate;
                        QString money;
                        QString other;
                        switch (billType) {
                        case 1://发票
                            type = "发票";
                            costType =true;
                            if(infoObj.contains("goods")){
                                QJsonValue goodsVal = infoObj.value("goods");
                                if(goodsVal.isString()){
                                    billContent = goodsVal.toString();
                                    billGoods = billContent;
                                    qDebug()<<"billGoods:"<<billGoods;
                                }
                            }
                            if(infoObj.contains("date")){
                                QJsonValue dateVal = infoObj.value("date");
                                if(dateVal.isString()){
                                    fbillDate = dateVal.toString();
                                }
                            }
                            if(infoObj.contains("price")){
                                QJsonValue priceVal = infoObj.value("price");
                                if(priceVal.isString()){
                                    money = priceVal.toString();
                                    billPrice = money;
                                }
                            }
                            if(infoObj.contains("number")){
                                QJsonValue numberVal = infoObj.value("number");
                                if(numberVal.isString()){
                                    other = numberVal.toString();
                                    billNumber = other;
                                }
                            }
                            if(infoObj.contains("code")){
                                QJsonValue numberVal = infoObj.value("code");
                                if(numberVal.isString()){
                                    billCode = numberVal.toString();
                                }
                            }
                            if(infoObj.contains("checkCode")){
                                QJsonValue numberVal = infoObj.value("checkCode");
                                if(numberVal.isString()){
                                    billCheckcode = numberVal.toString();
                                }

                            }
//                            emit costDone ();

                            break;
                        case 2://火车票
                            busiType =true;
                            type = "火车票";
                            if(infoObj.contains("person")){
                                QJsonValue personVal = infoObj.value("person");
                                if(personVal.isString()){
                                    user = personVal.toString();
                                    trainPerson =user;
                                }
                            }
                            if(infoObj.contains("date")){
                                QJsonValue dateVal = infoObj.value("date");
                                if(dateVal.isString()){
                                    billDate = dateVal.toString();
                                    trainDate = billDate;
                                }
                            }
                            if(infoObj.contains("departure")){
                                QJsonValue departureVal = infoObj.value("departure");
                                if(departureVal.isString()){
                                    start = departureVal.toString();
                                    trainStart = start;
                                }
                            }
                            if(infoObj.contains("price")){
                                QJsonValue priceVal = infoObj.value("price");
                                if(priceVal.isString()){
                                    money = priceVal.toString();
                                    trainPrice = money;
                                }
                            }
                            if(infoObj.contains("destination")){
                                QJsonValue destinationVal = infoObj.value("destination");
                                if(destinationVal.isString()){
                                    end = destinationVal.toString();
                                    trainEnd = end;
                                }
                            }
                            break;
                        case 3://飞机票
                            abroadType = true;
                            type = "飞机票";
                            if(infoObj.contains("person")){
                                QJsonValue personVal = infoObj.value("person");
                                if(personVal.isString()){
                                    user = personVal.toString();
                                }
                            }
                            if(infoObj.contains("date")){
                                QJsonValue dateVal = infoObj.value("date");
                                if(dateVal.isString()){
                                    billDate = dateVal.toString();
                                }
                            }
                            if(infoObj.contains("departure")){
                                QJsonValue departureVal = infoObj.value("departure");
                                if(departureVal.isString()){
                                    start = departureVal.toString();
                                }
                            }
                            if(infoObj.contains("price")){
                                QJsonValue priceVal = infoObj.value("price");
                                if(priceVal.isString()){
                                    money = priceVal.toString();
                                }
                            }
                            if(infoObj.contains("destination")){
                                QJsonValue destinationVal = infoObj.value("destination");
                                if(destinationVal.isString()){
                                    end = destinationVal.toString();
                                }
                            }

                            break;
                        case 4://出租车票
                            type = "出租车票";

                        default:
                            break;
                        }

                        scanInfo info;
                        info.billMoney = money;  //金额
                        info.billCode = billCode;     //编号
                        info.billContext = billContent;    //内容
                        info.billUse = type;    //备注，发票暂时没有合适的值，先用类型代替

                        emit fapiaoDone(info);
                    }
                }
            }
        }

    }

}
