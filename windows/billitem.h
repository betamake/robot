#ifndef BILLITEM_H
#define BILLITEM_H

#include <QWidget>
#include <QButtonGroup>
#include <QtWebEngineWidgets>
#include <QDialog>
#include <QStackedLayout>
#include "interfaceuser.h"
/*
@brief:发票itemview类
@time:2019-10-21
*/
namespace Ui {
class billItem;
}

class billItem : public QWidget
{
    Q_OBJECT

public:
    explicit billItem(QWidget *parent = nullptr);
    ~billItem();

    void setIndex(int index);

    void setType(QString type);
    void setInvoiceNumber(QString number);

    void setAttachmentType(QString type);

    void setCode(QString strCode);
    void setPath(QString strPath);
    QByteArray InitGetRequest(QString url,QString obj);
signals:
    void startBill(int type, int index);

public slots:
    void connfirmed(int index);

private slots:
    void on_billEmitBtn_clicked();
    void on_pushButton_clicked();

private:
    Ui::billItem *ui;
    QButtonGroup *group;

    int iIndex;
    QString type;       //0为纸质发票，1为电子发票
    QString invoiceNum;
    QString attachmentType;     //附件类型
    QString billCode;
    QString billPath;

    QWebEngineView *m_webView;
    QDialog *dialog;
};

#endif // BILLITEM_H
