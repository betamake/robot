#ifndef DOCUMENTJSON_H
#define DOCUMENTJSON_H

#include <QString>

class DocumentJson
{
public:
    DocumentJson();

private:
    QString attachmentId;           //单据附件id
    QString attachmentName;         //单据附件名称
    QString attachmentPath;         //单据附件path
    QString attachmentType;         //单据附件类型

    QString billCode;   //单据编码
    QString billId;     //单据id

    QString id;

    QString invoiceBuyAddress;      //购买方-地址
    QString invoiceBuyBankAccount;  //购买方-银行账号
    QString invoiceBuyBankName;     //购买方-开户行
    QString invoiceBuyPhone;        //购买方-电话
    QString invoiceBuyTaxNo;        //购买方-税号
    QString invoiceBuyTitle;        //购买方-抬头

    QString invoiceContent;         //发票内容
    QString invoiceMemo;            //发票备注
    QString invoiceMoney;           //金额
    QString invoiceNum;             //发票号码

    QString invoiceSaleAddress;     //销售方-地址
    QString invoiceSaleBankAccount; //销售方-银行账号
    QString invoiceSaleBankName;    //销售方-开户行
    QString invoiceSalePhone;       //销售方-电话
    QString invoiceSaleTaxNo;       //销售方-税号
    QString invoiceSaleTitle;       //销售方-抬头

    QString paperId;    //扫描附件id
    QString paperName;  //扫描附件名称
    QString paperPath;  //扫描附件路径
};

#endif // DOCUMENTJSON_H
