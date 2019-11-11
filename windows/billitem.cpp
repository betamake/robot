#include "billitem.h"
#include "ui_billitem.h"

billItem::billItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::billItem)
{
    ui->setupUi(this);
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
        ui->radioButton_2->clicked(true);
    }
    else
        ui->radioButton->clicked(true);
}

void billItem::setCode(QString strCode)
{
    billCode = strCode;
    ui->billNumber->setText(billCode);
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
