#include "scheduleitem.h"
#include "ui_scheduleitem.h"

scheduleItem::scheduleItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::scheduleItem)
{
    ui->setupUi(this);

    iType = -1;
    iIndex = -1;
}

scheduleItem::~scheduleItem()
{
    delete ui;
}

void scheduleItem::setTypeAndIndex(int type, int index)
{
    iType = type;
    iIndex = index;
}
/**
 * @brief 票据提交按钮
 * @param 无
 * @return 无
 * @time 2019-10-21
 */
void scheduleItem::on_scheduleEmitBtn_clicked()
{
    startSchedule(iType, iIndex);
}
