#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCurrentIndex(0);
    VoiceControl = new voiceControl(this);
    VoiceControl->initMedia();

}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
@brief:实现页面跳转
@param:currentIndex:页号
@return:无
@time:2019-10-17
*/
void MainWindow::setCurrentIndex(int currentIndex)
{
    int index = currentIndex;
    ui->stackedWidget->setCurrentIndex(index);
}
/*
@brief:欢迎页账号登录按钮，跳转到账号登录页面
@param:无
@return:无
@time:2019-10-17
*/
void MainWindow::on_accountButton_clicked()
{
    VoiceControl->player->stop();
    VoiceControl->sendPlayText("请输入账号密码");
    this->setCurrentIndex(1);
}
/*
@brief:账号登录
@param:无
@return:无
@time:2019-10-17
*/
void MainWindow::on_accountLoginButton_clicked()
{
    QString username = ui->accountUserEdit->text();
    QString password = ui->accountPasswordEdit->text();
    InterfaceUser = new interfaceUser(); //用户接口对象
    InterfaceUser->setUsername(username);
    InterfaceUser->setPassword(password);
    InterfaceUser->run();
    connect(InterfaceUser,SIGNAL(UserLoginDone(QString ,QString )),this,SLOT(dealUserLoginDone(QString ,QString )));
}
/*
@brief:处理账号返回信息，msg为登陆成功则跳转。
@param:realName 登录用户名，getMsg:登录的返回信息
@return:无
@time:2019-10-19
*/
void MainWindow::dealUserLoginDone(QString realName,QString getMsg)
{
    QString username = realName;

   QString msg = getMsg;
   if(msg == "登录成功")
   {
       this->setCurrentIndex(6);

   }
   else {
       QMessageBox::information(this, QString::fromUtf8("用户名或密码错误"),QString::fromUtf8("请核对用户名密码"));
   }
}
/*
@brief:处理账号返回信息，msg为登陆成功则跳转。否则跳转到注册
@param:realName 登录用户名，getMsg:登录的返回信息
@return:无
@time:2019-10-19
*/
void MainWindow::on_faceButton_clicked()
{
    VoiceControl->player->stop();
    VoiceControl->sendPlayText("请把人脸放入框内");
    this->setCurrentIndex(2);
    qDebug()<<"人脸登录"<<CameraDevice::getinstance ()->CameraInfo.getviewfinder ();
     ui->imageLayout->addWidget(CameraDevice::getinstance ()->CameraInfo.getviewfinder ());
     CameraDevice::getinstance ()->CameraInfo.getcamera ()->start();
     CameraDevice::getinstance ()->moveToThread (CameraDevice::getinstance ()); //解决类不在一个线程
     CameraDevice::getinstance ()->start ();
     // jump to facecheck page
     this->setCurrentIndex(2);
      connect (CameraDevice::getinstance (),SIGNAL(faceCheckDone()),this,SLOT(dealFaceCheckDone()));
     connect (CameraDevice::getinstance (),SIGNAL(faceCheckFailure()),this,SLOT(dealFaceCheckFailure()));
}
/*
@brief:处理账号返回信息，msg为登陆成功则跳转到材料提交页。
@param:无
@return:无
@time:2019-10-19
*/
void MainWindow::dealFaceCheckDone ()
{
    CameraDevice::getinstance ()->quit ();
    CameraDevice::getinstance ()->wait ();
    this->setCurrentIndex(5);
}
/*
@brief:处理账号返回信息，msg为登陆成功则跳转到材料提交页。
@param:无
@return:无
@time:2019-10-19
*/
void MainWindow::dealFaceCheckFailure ()
{
    QMessageBox::information(this, QString::fromUtf8("未检测到您"),QString::fromUtf8("请注册"));
    this->setCurrentIndex(3);
    CameraDevice::getinstance ()->quit ();
    CameraDevice::getinstance ()->wait ();

}
/*
@brief:人脸注册获取用户名和密码
@param:无
@return:无
@time:2019-10-19
*/
void MainWindow::on_RegAcountBtn_clicked()
{
    InterfaceUser->setUsername (ui->RegUsername_LineEdit->text());
    InterfaceUser->setPassword (ui->RegPwd_LineEdit->text());
    ui->faceRegImageLayout->addWidget(faceReg::getinstance ()->CameraInfo.getviewfinder ());
    faceReg::getinstance ()->CameraInfo.getcamera ()->start();
    faceReg::getinstance ()->moveToThread (faceReg::getinstance ()); //解决类不在一个线程
    faceReg::getinstance ()->start ();
    connect(faceReg::getinstance (),SIGNAL(faceRegSucess()),this,SLOT(dealFaceRegSucess()));
    connect(faceReg::getinstance (),SIGNAL(faceRegFailure()),this,SLOT(dealFaceRegFailure()));
}
/*
@brief:注册成功返回首页
@param:无
@return:无
@time:2019-10-19
*/
void MainWindow::dealFaceRegSucess ()
{
    this->setCurrentIndex(0);
    faceReg::getinstance ()->quit ();
    faceReg::getinstance ()->wait ();
    ui->RegPwd_LineEdit->clear();
    ui->RegPwd_LineEdit->clear();
}
/*
@brief:注册失败重新注册
@param:无
@return:无
@time:2019-10-19
*/
void MainWindow::dealFaceRegFailure ()
{
    QMessageBox::information(this, QString::fromUtf8("注册失败"),QString::fromUtf8("请重新注册"));
    this->setCurrentIndex(3);
    faceReg::getinstance ()->quit ();
    faceReg::getinstance ()->wait ();
}
/*
@brief:首页按钮。
@param:无
@return:无
@time:2019-10-19
*/
void MainWindow::on_firstButton_clicked()
{
    this->setCurrentIndex(0);
//    switch (currentIndex) {
//    case 1:

//    }
}

void MainWindow::on_idCardButton_clicked()
{

}
