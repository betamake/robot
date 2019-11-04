#include "billidentify.h"

BillIdentify::BillIdentify(QObject *parent) : QThread(parent)
{
    address = "http://192.168.3.185:8000";
}
void BillIdentify::run()
{
    qDebug () <<"111";
    QString runpath= QCoreApplication::applicationDirPath();
    QString fileName=runpath+"/finalbill.jpg";

    qDebug()<<"runpath:"<<runpath;
    qDebug() << "fileName:" << fileName;
        manager = new QNetworkAccessManager(this);
        //读取完成后识别票据
        QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(billReply(QNetworkReply*)));

        QFile file(fileName);
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

//        //打印票据图片编码
//        this->printFile("billReply.txt", fdata);
//        //    QString address = HOST.append("/bill/");

        QNetworkRequest request = HttpRequest.getHttpRequest(address.left(25).append("/bill/"));
        request.setHeader(QNetworkRequest::ContentLengthHeader, data.size());
        manager->post(request,params.toString().toUtf8());
        exec() ;
}
/**
* @brief       票据识别返回处理
* @author        胡帅成
* @date        2018-09-06
*/
void BillIdentify::billReply(QNetworkReply * reply){
    //打印结果
    qDebug() << "------票据识别结果------"<<reply->error()<< endl;
    emit success();
    if(reply->error() ==    QNetworkReply::NoError){
        QByteArray all = reply->readAll();
        qDebug()<<endl<<endl<<all<<endl;
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
                        //保存票据电子版附件
                        QString baseDir = QCoreApplication::applicationDirPath();
                        QString fileDir = baseDir.append("/files/bill/");
                        //创建目录
                        QDir dir;
                        if(!dir.exists(fileDir))
                        {
                            bool res = dir.mkpath(fileDir);
                            qDebug() << "创建保存票据电子版图片目录结果:" << res;
                        }
                        fileDir.append(HttpRequest.getCurrentTime());

                        //获得票据附件名称
                        QFileInfo filinfo;
                        filinfo = QFileInfo(fileDir);
                        billname = filinfo.fileName();
                        qDebug()<<"billname"<<billname;
                        fileDir.append(".jpg");
                        billdir = fileDir;
                        qDebug()<<"billdir"<<billdir;
                        blpath.append(billdir);
                        QImage img(billpath);
                        QPixmap pixmap = QPixmap::fromImage(img);
                        pixmap.save(fileDir);
                        bldir.append(billname);//保存票据识别的附件名称
//                        allInterface::getinstance ()->info.setuploadPath (billdir);
//                        allInterface::getinstance ()->getUploadFile ();
                        int billType = 0;
                        if(object.contains("type")){
                            QJsonValue typeVal = object.value("type");
                            if(typeVal.isDouble()){
                                billType = typeVal.toInt();
//                                bill.setBilltype(QString(billType));//票据类别
                            }
                        }
                        QJsonObject infoObj;
                        if(object.contains("info")){
                            QJsonValue infoVal = object.value("info");
                            if(infoVal.isObject()){
                                infoObj = infoVal.toObject();
                            }
                        }

                        /* {
                            "success": 1,
                            "type": 1,
                            "info": {
                                "code": "1100171320",
                                "number": "39283562",
                                "date": "2017年08月13日",
                                "goods": "餐费",
                                "price": "1888.00",
                                "checkCode": "04844754757667122571"
                            }
                        }
                        */

                        /*
                            QString billID;//报销人id
                            QString billExpenseid;
                            QString billAttachmenttitle;//附件名称
                            QString billRealpath;//文件保存路径
                            QString billType;//票据类型
                            QString billContent;//票据名目
                            QString billCode;//票据代码
                            QString billNumber;//票据号码
                            QString billUser;//火车票、飞机票乘车人
                            QString billStartplace;//始发站
                            QString billEndplace;//终点站
                            QString billDate;//发票日期、乘车日期
                            QString billMoney;//票据金额
                            QString billCheckcode;//校验码
                            QString billOther;//发票的号码*/

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
//                            bill.setBilltype(type);
                            if(infoObj.contains("goods")){
                                QJsonValue goodsVal = infoObj.value("goods");
                                if(goodsVal.isString()){
                                    billContent = goodsVal.toString();
                                    billGoods = billContent;
                                    qDebug()<<"billGoods:"<<billGoods;
//                                    bill.setBillcontent(billContent);
                                }
                            }
                            if(infoObj.contains("date")){
                                QJsonValue dateVal = infoObj.value("date");
                                if(dateVal.isString()){
                                    fbillDate = dateVal.toString();

//                                    bill.setBilldate(fbillDate);
                                }
                            }
                            if(infoObj.contains("price")){
                                QJsonValue priceVal = infoObj.value("price");
                                if(priceVal.isString()){
                                    money = priceVal.toString();
                                    billPrice = money;
//                                    bill.setBillmoney(money);
                                }
                            }
                            if(infoObj.contains("number")){
                                QJsonValue numberVal = infoObj.value("number");
                                if(numberVal.isString()){
                                    other = numberVal.toString();
                                    billNumber = other;
//                                    bill.setBillnumber(other);
                                }
                            }
                            if(infoObj.contains("code")){
                                QJsonValue numberVal = infoObj.value("code");
                                if(numberVal.isString()){
                                    billCode = numberVal.toString();
//                                    bill.setBillcode(numberVal.toString());
                                }
                            }
                            if(infoObj.contains("checkCode")){
                                QJsonValue numberVal = infoObj.value("checkCode");
                                if(numberVal.isString()){
                                    billCheckcode = numberVal.toString();
//                                    bill.setBillcheckcode(numberVal.toString());
                                }

                            }
//                            emit costDone ();

                            break;
                        case 2://火车票
                            busiType =true;
//                            player->stop();
//                            this->sendPlayText("火车票识别成功");
//                            bill.setBilltype("火车票");
                            type = "火车票";
//                            bill.setBilltype(type);

                            if(infoObj.contains("person")){
                                QJsonValue personVal = infoObj.value("person");
                                if(personVal.isString()){
                                    user = personVal.toString();
                                    trainPerson =user;
//                                    bill.setBilluser(user);
                                }
                            }
                            if(infoObj.contains("date")){
                                QJsonValue dateVal = infoObj.value("date");
                                if(dateVal.isString()){
                                    billDate = dateVal.toString();
                                    trainDate = billDate;
//                                    bill.setBilldate(billDate);
                                }
                            }
                            if(infoObj.contains("departure")){
                                QJsonValue departureVal = infoObj.value("departure");
                                if(departureVal.isString()){
                                    start = departureVal.toString();
                                    trainStart = start;
//                                    bill.setBillstartplace(start);
                                }
                            }
                            if(infoObj.contains("price")){
                                QJsonValue priceVal = infoObj.value("price");
                                if(priceVal.isString()){
                                    money = priceVal.toString();
                                    trainPrice = money;
//                                    bill.setBillmoney(money);
                                }
                            }
                            if(infoObj.contains("destination")){
                                QJsonValue destinationVal = infoObj.value("destination");
                                if(destinationVal.isString()){
                                    end = destinationVal.toString();
                                    trainEnd = end;
//                                    bill.setBillendplace(end);
                                }
                            }
//                            emit busiDone ();
                            break;
                        case 3://飞机票
                            abroadType = true;
//                            player->stop();
//                            this->sendPlayText("飞机票识别成功");
                            type = "飞机票";
//                            bill.setBilltype(type);

                            if(infoObj.contains("person")){
                                QJsonValue personVal = infoObj.value("person");
                                if(personVal.isString()){
                                    user = personVal.toString();
//                                    bill.setBilluser(user);
                                }
                            }
                            if(infoObj.contains("date")){
                                QJsonValue dateVal = infoObj.value("date");
                                if(dateVal.isString()){
                                    billDate = dateVal.toString();
//                                    bill.setBilldate(billDate);
                                }
                            }
                            if(infoObj.contains("departure")){
                                QJsonValue departureVal = infoObj.value("departure");
                                if(departureVal.isString()){
                                    start = departureVal.toString();
//                                    bill.setBillstartplace(start);
                                }
                            }
                            if(infoObj.contains("price")){
                                QJsonValue priceVal = infoObj.value("price");
                                if(priceVal.isString()){
                                    money = priceVal.toString();
//                                    bill.setBillmoney(money);
                                }
                            }
                            if(infoObj.contains("destination")){
                                QJsonValue destinationVal = infoObj.value("destination");
                                if(destinationVal.isString()){
                                    end = destinationVal.toString();
//                                    bill.setBillendplace(end);
                                }
                            }
//                            emit abroadDone ();

                            break;
                        case 4://出租车票
//                            player->stop();
//                            this->sendPlayText("出租车票识别成功");
                            type = "出租车票";
//                            bill.setBilltype(type);

                        default:
                            break;
                        }

//                        QListWidgetItem *item = new QListWidgetItem();
//                        item->setSizeHint(QSize(760,90));

//                        billItem *billItemView = new billItem();
//                        billItemView->setBillInfo(bill);

//                        billItemView->setBillType(billType);
//                        billItemView->setBillAccount(bill.getBillmoney());
//                        billItemView->setBillPixmap(pixmap);
//                        if(billType == 2 || billType == 3) {
//                            billItemView->setDeparture(bill.getBillstartplace());
//                            billItemView->setDestination(bill.getBillendplace());
//                        }

//                        ui->billListWidget->addItem(item);
//                        ui->billListWidget->setItemWidget(item, billItemView);

//                        billList.append(bill);

//                        int row = ui->billListWidget->row(item);
//                        billItemView->setIndex(row);

//                        connect(billItemView, &billItem::openBillItem, this, &MainWindow::openBillItemDialog);
//                        connect(billItemView, &billItem::deleteBillItem, this, &MainWindow::deleteBillItemView);

                    }
                }
            }
        }

    }

}
