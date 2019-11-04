#include "documentjson.h"

DocumentJson::DocumentJson()
{
    clearValue();
}

void DocumentJson::clearValue()
{
    attachmentId = "";           //单据附件id
    attachmentName = "";         //单据附件名称
    attachmentPath = "";         //单据附件path
    attachmentType = "";         //单据附件类型

    billCode = "";   //单据编码
    billId = "";     //单据id

    id = "";

    invoiceBuyAddress = "";      //购买方-地址
    invoiceBuyBankAccount = "";  //购买方-银行账号
    invoiceBuyBankName = "";     //购买方-开户行
    invoiceBuyPhone = "";        //购买方-电话
    invoiceBuyTaxNo = "";        //购买方-税号
    invoiceBuyTitle = "";        //购买方-抬头

    invoiceContent = "";         //发票内容
    invoiceMemo = "";            //发票备注
    invoiceMoney = "";           //金额
    invoiceNum = "";             //发票号码

    invoiceSaleAddress = "";     //销售方-地址
    invoiceSaleBankAccount = ""; //销售方-银行账号
    invoiceSaleBankName = "";    //销售方-开户行
    invoiceSalePhone = "";       //销售方-电话
    invoiceSaleTaxNo = "";       //销售方-税号
    invoiceSaleTitle = "";       //销售方-抬头

    paperId = "";    //扫描附件id
    paperName = "";  //扫描附件名称
    paperPath = "";  //扫描附件路径
}

/**
 * @brief DocumentJson::buildJsonObject
 * @return 拼接的JsonObject，在提交的时候要放入QDocument里
 */
QJsonObject DocumentJson::buildJsonObject()
{
    QJsonObject object;

    object.insert("attachmentId", attachmentId);
    object.insert("attachmentName", attachmentName);
    object.insert("attachmentPath", attachmentPath);
    object.insert("attachmentType", attachmentType);

    object.insert("billCode", billCode);
    object.insert("billId", billId);

    object.insert("id", id);

    object.insert("invoiceBuyAddress", invoiceBuyAddress);
    object.insert("invoiceBuyBankAccount", invoiceBuyBankAccount);
    object.insert("invoiceBuyBankName", invoiceBuyBankName);
    object.insert("invoiceBuyPhone", invoiceBuyPhone);
    object.insert("invoiceBuyTaxNo", invoiceBuyTaxNo);
    object.insert("invoiceBuyTitle", invoiceBuyTitle);

    object.insert("invoiceContent", invoiceContent);
    object.insert("invoiceMemo", invoiceMemo);
    object.insert("invoiceMoney", invoiceMoney);
    object.insert("invoiceNum", invoiceNum);

    object.insert("invoiceSaleAddress", invoiceSaleAddress);
    object.insert("invoiceSaleBankAccount", invoiceSaleBankAccount);
    object.insert("invoiceSaleBankName", invoiceSaleBankName);
    object.insert("invoiceSalePhone", invoiceSalePhone);
    object.insert("invoiceSaleTaxNo", invoiceSaleTaxNo);
    object.insert("invoiceSaleTitle", invoiceSaleTitle);

    object.insert("paperId", paperId);
    object.insert("paperName", paperName);
    object.insert("paperPath", paperPath);

    return object;
}
