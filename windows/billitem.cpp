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

    ui->radioButton->hide();
    ui->radioButton_2->hide();

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
    if (type == "F01") {
        ui->radioButton->show();
        ui->radioButton_2->show();
        if(type == "0"){
            ui->radioButton_2->setChecked(true);
        }
        else
            ui->radioButton->setChecked(true);
    } else {
        ui->radioButton->hide();
        ui->radioButton_2->hide();
    }
}

void billItem::setAttachmentType(QString type)
{
    attachmentType = type;
    if (type == "F01") {
        ui->radioButton->show();
        ui->radioButton_2->show();
    } else {
        ui->radioButton->hide();
        ui->radioButton_2->hide();
    }
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
//    dialog  = new QDialog(this);
//    dialog->resize(600,600);
//    m_webView = new QWebEngineView(dialog);
//    QStackedLayout* layout = new QStackedLayout(dialog);
//    dialog->setLayout(layout);
//    layout->addWidget(m_webView);
//    qDebug()<<"path:"<<path;
//    m_webView->load(QUrl(path));
//    m_webView->resize(500,500);
//    m_webView->show();
//    dialog->show();
}
