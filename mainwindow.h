﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interfaceuser.h"
#include "cameradevice.h"
#include "facereg.h"
#include "windows/billitem.h"
#include "voicecontrol.h"
#include "qrdecode.h"
#include "billidentify.h"
#include <QQuickView>
#include "turing.h"
#include "scanpage.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/*
@brief:主程序类
@time:2019-10-17
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setCurrentIndex(int currentIndex); //实现页面跳转;
    void getDocumentsListWidget(int index);   //附件列表页实现
    void ceshiButton();//测试人脸登录，后面删除。
    void userLogin(); //用户登录；

signals:
    void confirmAttDone(int index);

private:
    void initView();

private slots:
    void startBillEmit();  //点击选择票据列表中的“提交票据”按钮，转入报销页面

    void getAllBills();             //获得票据列表
    void getAttachments();          //获得单据列表

    void startEmit(int type, int index);    //获得要提交的票据的信息，用于和扫描的结果对比

    void getBillInfo(QString code, QString money, QString context, QString use);    //获得扫描的票据的信息
    void setBillInfo();     //扫描结果显示
    void dealScanDone();
    void dealQrDone(QString billCode);

private slots:
    void on_accountButton_clicked();

    void on_accountLoginButton_clicked();
    void dealUserLoginDone(QString realName,qint16 getMsg);

    void on_faceButton_clicked();
    void dealFaceCheckDone();
    void dealFaceCheckFailure();

    void on_RegAcountBtn_clicked();
    void dealFaceRegSucess ();
    void dealFaceRegFailure ();
    
    void on_firstButton_clicked();

    void on_emitFinishBtn_clicked();

    void on_emitCancelBtn_clicked();

    void on_shouyePostButton_clicked();

    void on_scanStartBtn_clicked();

    void on_confirmBtn_clicked();
    void on_scanAgainBtn_clicked();
    void on_idCardButton_clicked();
    void on_zhichuButton_clicked();

    void on_chaiLvButton_clicked();
    void on_chuguoButton_clicked();
    void on_qingkuanButton_clicked();
    void on_huankuanButton_clicked();
    void on_neibuButton_clicked();
    void on_lingyongButton_clicked();
    void on_zhanshouButton_clicked();

    void on_postBillButton_clicked();

    void on_ceShiButton_clicked();
    void deal_ceShiButton_clicked();
    void on_chatButton_clicked();

    void on_pushButton_clicked();

    void on_scanBackBtn_clicked();

private:
    Ui::MainWindow *ui;
    int currentIndex; //当前页号
    voiceControl  *VoiceControl;
    BillIdentify *billIndentify;
    Turing *turing;
    QString loginType;

    QButtonGroup *btnGroup;

    QList<billInfo> mBillList;
    QList<attachment> mAttachmentList;
//    QList<attachment> mBillAttList;      //发票列表=============>附件列表
//    QList<attachment> mOtherAttList;     //其他列表=============>弃置
    QMap<QString, QString>  mAttachmentTypeList;    //附件类型列表
//    int attType;    //票据类型  0为发票，1为其他
    int attIndex;   //票据序号

    QString mFapiaoCode;    //需要提交的发票的code,用于比较扫描出来的是否一致
    scanInfo mFapiaoInfo;   //识别出来的发票的信息

    ScanPage *scanPage;
};
#endif // MAINWINDOW_H
