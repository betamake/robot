//#pragma execution_character_set(“utf-8”)
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

void scheduleItem::setCode(QString strCode)
{
    mCode = strCode;
}

void scheduleItem::setName(QString name)
{
    ui->indexLabel->setText(name);
}
void scheduleItem::setPath(QString strPath)
{
    billPath = strPath;
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

void scheduleItem::connfirmed(int type, int index)
{
    if ((type == 1) && (index==iIndex))
    {
        ui->scheduleEmitBtn->setText("已提交");
        ui->scheduleEmitBtn->setDisabled(true);
    }
}

void scheduleItem::on_pushButton_clicked()
{
    QString path = "http://211.157.179.73:9720/admin/review/view?path="+billPath;
    dialog  = new QDialog(this);
    dialog->resize(600,600);
    m_webView = new QWebEngineView(dialog);
    QStackedLayout* layout = new QStackedLayout(dialog);
    dialog->setLayout(layout);
    layout->addWidget(m_webView);
    qDebug()<<"path:"<<path;
    m_webView->load(QUrl(path));
    m_webView->resize(500,500);
    m_webView->show();
    dialog->show();
}
