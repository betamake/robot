#ifndef DOCUMENTJSON_H
#define DOCUMENTJSON_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
/**
 * @brief The DocumentJson class
 * @details 用来拼接要上传的附件信息的json，有set方法
 * @details 可能要用作单例
 */
class DocumentJson
{
public:
    DocumentJson();

    //重置数据，用于下一次提交
    void clearValue();

    //构建QJsonDocument
    QJsonObject buildJsonObject();

    void setAttachmentId(QString attachmentId) { this->attachmentId = attachmentId;}
    void setAttachmentName(QString attachmentName) { this->attachmentName = attachmentName;}
    void setAttachmentPath(QString attachmentPath) { this->attachmentPath = attachmentPath;}
    void setAttachmentType(QString attachmentType) { this->attachmentType = attachmentType;}

    void setBillCode(QString billCode) { this->billCode = billCode;}
    void setBillId(QString billId) { this->billId = billId;}

    void setId(QString id) { this->id = id;}

    void setInvoiceBuyAddress(QString invoiceBuyAddress) { this->invoiceBuyAddress = invoiceBuyAddress;}
    void setInvoiceBuyBankAccount(QString invoiceBuyBankAccount) { this->invoiceBuyBankAccount = invoiceBuyBankAccount;}
    void setInvoiceBuyBankName(QString invoiceBuyBankName) { this->invoiceBuyBankName = invoiceBuyBankName;}
    void setInvoiceBuyPhone(QString invoiceBuyPhone) { this->invoiceBuyPhone = invoiceBuyPhone;}
    void setInvoiceBuyTaxNo(QString invoiceBuyTaxNo) { this->invoiceBuyTaxNo = invoiceBuyTaxNo;}
    void setInvoiceBuyTitle(QString invoiceBuyTitle) { this->invoiceBuyTitle = invoiceBuyTitle;}

    void setInvoiceContent(QString invoiceContent) { this->invoiceContent = invoiceContent;}
    void setInvoiceMemo(QString invoiceMemo) { this->invoiceMemo = invoiceMemo;}
    void setInvoiceMoney(QString invoiceMoney) { this->invoiceMoney = invoiceMoney;}
    void setInvoiceNum(QString invoiceNum) { this->invoiceNum = invoiceNum;}

    void setInvoiceSaleAddress(QString invoiceSaleAddress) { this->invoiceSaleAddress = invoiceSaleAddress;}
    void setInvoiceSaleBankAccount(QString invoiceSaleBankAccount) { this->invoiceSaleBankAccount = invoiceSaleBankAccount;}
    void setInvoiceSaleBankName(QString invoiceSaleBankName) { this->invoiceSaleBankName = invoiceSaleBankName;}
    void setInvoiceSalePhone(QString invoiceSalePhone) { this->invoiceSalePhone = invoiceSalePhone;}
    void setInvoiceSaleTaxNo(QString invoiceSaleTaxNo) { this->invoiceSaleTaxNo = invoiceSaleTaxNo;}
    void setInvoiceSaleTitle(QString invoiceSaleTitle) { this->invoiceSaleTitle = invoiceSaleTitle;}

    void setPaperId(QString paperId) { this->paperId = paperId;}
    void setPaperName(QString paperName) { this->paperName = paperName;}
    void setPaperPath(QString paperPath) { this->paperPath = paperPath;}

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
