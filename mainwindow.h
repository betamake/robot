#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interfaceuser.h"
#include "cameradevice.h"
#include "facereg.h"
#include "windows/billitem.h"
#include "windows/scheduleitem.h"
#include "voicecontrol.h"
#include "qrdecode.h"
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

    void getAllBills();             //获得票据列表

    void getDocumentsListWidget(int index);   //附件列表页实现

private slots:
    void startBillEmit();  //点击选择票据列表中的“提交票据”按钮，转入报销页面

    void startEmit(int type, int index);    //获得要提交的票据的信息，用于和扫描的结果对比

    void setBillInfo();     //扫描结果显示

private slots:
    void on_accountButton_clicked();

    void on_accountLoginButton_clicked();
    void dealUserLoginDone(QString realName,QString getMsg);

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
    void deal_zhichuButton_slot();

    void on_chaiLvButton_clicked();
    void deal_chaiLvButton_slot();
    void on_chuguoButton_clicked();
    void deal_chuguoButton_slot();
    void on_qingkuanButton_clicked();
    void deal_qingkuanButton_slot();
    void on_huankuanButton_clicked();
    void deal_huankuanButton_slot();
    void on_neibuButton_clicked();
    void deal_neibuButton_slot();
    void on_lingyongButton_clicked();
    void deal_lingyongButton_slot();
    void on_zhanshouButton_clicked();
    void deal_zhanshouButton_slot();

    void on_postBillButton_clicked();

    void on_ceShiButton_clicked();

private:
    Ui::MainWindow *ui;
    int currentIndex; //当前页号
    interfaceUser *InterfaceUser;
    voiceControl  *VoiceControl;
};
#endif // MAINWINDOW_H
