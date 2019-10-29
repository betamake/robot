#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interfaceuser.h"
#include "cameradevice.h"
#include "facereg.h"

#include "windows/billitem.h"
#include "windows/scheduleitem.h"

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

    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();

    void on_shouyePostButton_clicked();

    void on_scanStartBtn_clicked();

    void on_confirmBtn_clicked();
    void on_scanAgainBtn_clicked();

private:
    Ui::MainWindow *ui;
    int currentIndex; //当前页号
    interfaceUser *InterfaceUser;
};
#endif // MAINWINDOW_H
