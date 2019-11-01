#include "billidentify.h"

BillIdentify::BillIdentify(QObject *parent) : QThread(parent)
{
    address = "http://192.168.3.185:8000";
}
void BillIdentify::run()
{
    //    player->stop();
    //    this->sendPlayText("请选择票据");
        //定义文件对话框类
        fileDialog = new QFileDialog;
        //定义文件对话框标题
        fileDialog->setWindowTitle(tr("打开图片"));
        //设置默认文件路径
        fileDialog->setDirectory(".");
        //设置文件过滤器
        fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg)"));
        //设置视图模式
        fileDialog->setViewMode(QFileDialog::Detail);
        QStringList fileNames;
        if(fileDialog->exec()){
            fileNames = fileDialog->selectedFiles();
        }
        QString fileName;
        fileName = fileNames.at(0);
        billpath = fileName;
        qDebug()<<fileName<<endl;
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
}
