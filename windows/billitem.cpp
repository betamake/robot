//#pragma execution_character_set(“utf-8”)
#include "billitem.h"
#include "ui_billitem.h"
#include <QDebug>
billItem::billItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::billItem)
{
    ui->setupUi(this);

    group = new QButtonGroup(this);
    group->addButton(ui->radioButton, 0);      //电子发票
    group->addButton(ui->radioButton_2, 1);    //纸质发票
    ui->radioButton->setChecked(true);

    iIndex = -1;
}

billItem::~billItem()
{
    delete ui;
}

void billItem::setIndex(int index)
{
    iIndex = index;
}

void billItem::setType(QString type)
{
    if(type == "0"){
        ui->radioButton_2->setChecked(true);
    }
    else
        ui->radioButton->setChecked(true);
}

void billItem::setCode(QString strCode)
{
    billCode = strCode;
    ui->billNumber->setText(billCode);
}
void billItem::setPath(QString strPath)
{
    billPath = strPath;
}
/**
 * @brief 发票提交按钮
 * @param 无
 * @return 无
 * @time 2019-10-21
 */
void billItem::on_billEmitBtn_clicked()
{
    emit startBill(0, iIndex);
}

void billItem::connfirmed(int type, int index)
{
    if ((type == 0) && (index==iIndex))
    {
        ui->billEmitBtn->setText("已提交");
        ui->billEmitBtn->setDisabled(true);
    }
}
void billItem::on_pushButton_clicked()
{
    QString path = "http://211.157.179.73:9720/admin/review/view?path="+billPath;
//    QString path = "http://211.157.179.73:9720/admin/attachment/downloadByPath?downPath="+billPath;
    dialog  = new QDialog(this);
    dialog->resize(600,600);
//    m_webView = new QWebEngineView(dialog);
//    QStackedLayout* layout = new QStackedLayout(dialog);
//    dialog->setLayout(layout);
//    layout->addWidget(m_webView);
    qDebug()<<"path:"<<path;
//    m_webView->load(QUrl("http://211.157.179.73:9720/admin/attachment/downloadByPath?downPath=2019/11/19/05df46dc82067eea.jpg"));
//    m_webView->resize(500,500);
//    m_webView->show();
    QLabel *showLabel = new QLabel(dialog);
    showLabel->resize(600,600);
//    QFile file("C:\\Users\\betamake\\Pictures\\IMG_00000001.jpg");

//    if (!file.open(QIODevice::ReadOnly)||file.size()==0)
//    {
//        file.close();
//        qDebug() << "文件打开失败";
//    }
//    QByteArray jpegData = file.readAll();
//    file.close();
    QByteArray jpegData = interfaceUser::getinstance()->InitGetRequest("path","downImgFromUrl");
    QPixmap pixmap;
    pixmap.loadFromData(jpegData);
    showLabel->setPixmap(pixmap); // 你在QLabel显示图片
    dialog->show();
}
