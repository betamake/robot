#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->setCurrentIndex(0);
    this->setCurrentIndex(5);
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
       this->setCurrentIndex(5);

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
/**
 * @brief 首页-提交票据按钮
 */
void MainWindow::on_shouyePostButton_clicked()
{
    QMessageBox box(QMessageBox::Question, "", "请选择提交方式:", nullptr);
    QPushButton *btn1 = box.addButton("选择票据", QMessageBox::AcceptRole);
    QPushButton *btn2 = box.addButton("扫描", QMessageBox::RejectRole);
    box.exec();
    if (box.clickedButton() == btn1){
        this->setCurrentIndex(6);
        //to do
        getAllBills();

    } else if (box.clickedButton() == btn2){
        //页面还没有做好，稍等
        this->setCurrentIndex(6);
    }
}
/**
 * @brief 获得票据列表
 */
void MainWindow::getAllBills()
{
    //to do
    //获取当前登录人员的所有待处理的单据

    //目前还没有接口获得票据列表的操作，先留存

    //假设有两张票据
    int count = 2;

    ui->tableWidget->setRowCount(count);
    ui->tableWidget->setColumnCount(5);
    //清空内容但不清空表头
    ui->tableWidget->clearContents();

    for (int i=0; i<count; i++){
        QString numberStr = "0011";         //单据编号
        QString dateStr = "2019-10-22";     //日期
        double account = 1900.0;             //金额
        QString digestStr = "摘要";           //摘要

        QPushButton *btn = new QPushButton("提交票据");

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(numberStr));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(dateStr));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(account)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(digestStr));
        ui->tableWidget->setCellWidget(i, 4, btn);

        connect(btn, &QPushButton::clicked, this, &MainWindow::startBillEmit);
    }
}
/**
 * @brief 选择单据页面，点击一张单据提交按钮，打开对应的附件列表页
 */
void MainWindow::startBillEmit()
{
    int index = ui->tableWidget->currentRow();
    qDebug() << "选择了第" << index << "张票据" ;

    //从单据列表List中找到第index条项目，然后解析获得它的附件列表，接着填入附件列表页

    ui->stackedWidget->setCurrentIndex(7);
    getDocumentsListWidget(index);
}
/**
 * @brief 附件列表页实现
 * @param 附件列表
 * @return nothing
 * @time 2019-10-22
 */
void MainWindow::getDocumentsListWidget(int index)
{
    qDebug() << "打开了第" << index << "张票据" ;

    int billCount = 2;  //假设有2张发票
    int scheduleCount = 0;  //假设有0张会议日程
    int otherCount = 2; //假设有2张其他票据

    if (billCount > 0) {
        QListWidget *billsList = new QListWidget();
        QSize size = QSize(750, billCount * 110 + 50);
        billsList->setFixedSize(size);

        billsList->addItem("发票");

        for (int i = 0; i<billCount; i++){
            QListWidgetItem *item1 = new QListWidgetItem();
            item1->setSizeHint(QSize(720, 110));

            billItem *newItem = new billItem();
            newItem->setIndex(i);
            connect(newItem, &billItem::startBill, this, &MainWindow::startEmit);

            billsList->addItem(item1);
            billsList->setItemWidget(item1, newItem);
        }

        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(size);

        ui->billListWidget->addItem(item);
        ui->billListWidget->setItemWidget(item, billsList);
    }
    if (scheduleCount > 0) {
        QListWidget *othersList = new QListWidget();
        QSize size = QSize(750, scheduleCount * 110 + 50);
        othersList->setFixedSize(size);

        othersList->addItem("会议日程");

        for (int i=0; i<scheduleCount; i++) {
            QListWidgetItem *item1 = new QListWidgetItem();
            item1->setSizeHint(QSize(720, 110));

            scheduleItem *newItem = new scheduleItem();
            newItem->setTypeAndIndex(1, i);
            connect(newItem, &scheduleItem::startSchedule, this, &MainWindow::startEmit);

            othersList->addItem(item1);
            othersList->setItemWidget(item1, newItem);
        }

        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(size);

        ui->billListWidget->addItem(item);
        ui->billListWidget->setItemWidget(item, othersList);
    }
    if (otherCount > 0) {
        QListWidget *othersList = new QListWidget();
        QSize size = QSize(750, otherCount * 110 + 50);
        othersList->setFixedSize(size);

        othersList->addItem("其他");

        for (int i=0; i<otherCount; i++) {
            QListWidgetItem *item1 = new QListWidgetItem();
            item1->setSizeHint(QSize(720, 110));

            scheduleItem *newItem = new scheduleItem();
            newItem->setTypeAndIndex(2, i);
            connect(newItem, &scheduleItem::startSchedule, this, &MainWindow::startEmit);

            othersList->addItem(item1);
            othersList->setItemWidget(item1, newItem);
        }

        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(size);

        ui->billListWidget->addItem(item);
        ui->billListWidget->setItemWidget(item, othersList);
    }
}
/**
 * @brief 从附件列表对应项获得要提交的票据的信息，用于之后和扫描结果比对
 * @param type
 * @param index
 */
void MainWindow::startEmit(int type, int index)
{
    ui->stackedWidget->setCurrentIndex(8);
    if (type == 0) {
        //发票
        //在发票列表中查找相应的发票，用于比较发票是否正确

    } else if (type == 1) {
        //日程
        //在日程列表中查找相应的发票，用于比较发票是否正确

    } else if (type == 2) {
        //其他
        //在其他列表中查找相应的发票，用于比较发票是否正确

    }
}
/**
 * @brief 票据列表页面提交完成按钮
 * @param 无
 * @return 无
 * @time 2019-10-21
 */
void MainWindow::on_emitFinishBtn_clicked()
{

}
/**
 * @brief 票据列表页面取消按钮
 * @param 无
 * @return 无
 * @time 2019-10-21
 */
void MainWindow::on_emitCancelBtn_clicked()
{

}
/**
 * @brief 支出凭证
 */
void MainWindow::on_pushButton_2_clicked()
{

}
/**
 * @brief 差旅报销
 */
void MainWindow::on_pushButton_clicked()
{

}
/**
 * @brief 出国报销
 */
void MainWindow::on_pushButton_4_clicked()
{

}
/**
 * @brief 请款单
 */
void MainWindow::on_pushButton_3_clicked()
{

}
/**
 * @brief 还款单
 */
void MainWindow::on_pushButton_7_clicked()
{

}
/**
 * @brief 领用单
 */
void MainWindow::on_pushButton_6_clicked()
{

}
/**
 * @brief 暂收单
 */
void MainWindow::on_pushButton_5_clicked()
{

}
/**
 * @brief 开始扫描按钮
 */
void MainWindow::on_scanStartBtn_clicked()
{
    //to do
    //扫描的过程待实现

    //扫描成功并获取发票的信息后，跳转到详情页面
    // to do
    // 将扫描的信息放在发票结构体或类中，在详情页由发票类来获得需要的字段
    ui->stackedWidget->setCurrentIndex(9);
    setBillInfo();
}
/**
 * @brief 扫描结果显示
 */
void MainWindow::setBillInfo()
{
    //to do
    //全局发票结构体

    //发票信息
    ui->billAccount->setText("2200");       //金额
    ui->billNumber->setText("0011");        //发票号
    ui->billContext->setText("发票内容");   //发票内容
    ui->billRemarks->setText("发票备注");   //发票备注

    //销售方信息
    ui->solderTitle->setText("");
    ui->solderDutyParagraph->setText("");
    ui->solderBank->setText("");
    ui->solderBankNum->setText("");
    ui->solderPhone->setText("");
    ui->solderAddress->setText("");

    //购买方信息
    ui->buyerTitle->setText("");
    ui->buyerDutyParagraph->setText("");
    ui->buyerBank->setText("");
    ui->buyerBankNum->setText("");
    ui->buyerPhone->setText("");
    ui->buyerAddress->setText("");
}
/**
 * @brief 发票信息页面：确认并返回按钮
 */
void MainWindow::on_confirmBtn_clicked()
{
    //to do
    //从全局的发票结构体中获得需要显示的字段并显示在相应的edit中


}
/**
 * @brief 发票信息页面：重新扫描按钮
 */
void MainWindow::on_scanAgainBtn_clicked()
{
    //to do
}
