#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interfaceuser.h"
#include "cameradevice.h"
#include "facereg.h"
#include "voicecontrol.h"
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

private:
    Ui::MainWindow *ui;
    int currentIndex; //当前页号
    interfaceUser *InterfaceUser;
    voiceControl  *VoiceControl;
};
#endif // MAINWINDOW_H
