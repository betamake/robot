#include "billitem.h"
#include "ui_billitem.h"

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
