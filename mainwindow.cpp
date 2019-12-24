#if _MSC_VER >= 1600	// MSVC2015 > 1899,	MSVC_VER = 14.0
#pragma execution_character_set("utf-8")
#endif
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCurrentIndex(0);
//    VoiceControl = new voiceControl(this);
//    VoiceControl->initMedia();

    initView();

    mBillList.clear();
    mAttachmentList.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initView()
{
    ui->userLabel->hide();

    btnGroup = new QButtonGroup();
    btnGroup->addButton(ui->zhichuButton);
    btnGroup->addButton(ui->chaiLvButton);
    btnGroup->addButton(ui->chuguoButton);
    btnGroup->addButton(ui->qingkuanButton);
    btnGroup->addButton(ui->huankuanButton);
    btnGroup->addButton(ui->neibuButton);
    btnGroup->addButton(ui->lingyongButton);
    btnGroup->addButton(ui->zhanshouButton);
    btnGroup->setExclusive(true);


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
//    VoiceControl->player->stop();
//    VoiceControl->sendPlayText("请输入账号密码");
    ui->RegPwd_LineEdit->setEchoMode(QLineEdit::Password);
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
    interfaceUser::getinstance()->setUsername(username);
    interfaceUser::getinstance()->setPassword(password);
    this->userLogin();

    ui->accountUserEdit->clear();
    ui->accountPasswordEdit->clear();
    ui->userLabel->show();
}
void MainWindow::userLogin()
{
    interfaceUser::getinstance()->userLogin();
    connect(interfaceUser::getinstance(),SIGNAL(UserLoginDone(QString ,qint16 )),this,SLOT(dealUserLoginDone(QString ,qint16 )));
}
/*
@brief:处理账号返回信息，msg为登陆成功则跳转。
@param:realName 登录用户名，getMsg:登录的返回信息
@return:无
@time:2019-10-19
*/
void MainWindow::dealUserLoginDone(QString realName,qint16 getMsg)
{
    QString username = realName;

   qint16 msg = getMsg;
   qDebug()<<"msg:"<<msg;
   if(msg == 0)
   {
       this->setCurrentIndex(5);
       qDebug()<<"当前用户："<<realName;
       ui->userInfoLabel->setText(realName);
   }
   else {
       if (loginType =="face"){
           QMessageBox::information(this, QString::fromUtf8("人脸与用户民不匹配"),QString::fromUtf8("请重新注册"));
           this->setCurrentIndex(3);
       }
       else {
           QMessageBox::information(this, QString::fromUtf8("用户名或密码错误"),QString::fromUtf8("请核对用户名密码"));
       }
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
//    VoiceControl->player->stop();
//    VoiceControl->sendPlayText("请把人脸放入框内");
    this->setCurrentIndex(2);
    qDebug()<<"人脸登录"<<CameraDevice::getinstance ()->CameraInfo.getviewfinder ();
     ui->imageLayout->addWidget(CameraDevice::getinstance ()->CameraInfo.getviewfinder ());
     CameraDevice::getinstance ()->CameraInfo.getcamera ()->start();
     CameraDevice::getinstance ()->moveToThread (CameraDevice::getinstance ()); //解决类不在一个线程
     CameraDevice::getinstance ()->start ();

     connect (CameraDevice::getinstance (),SIGNAL(faceCheckDone()),this,SLOT(dealFaceCheckDone()));
     connect (CameraDevice::getinstance (),SIGNAL(faceCheckFailure()),this,SLOT(dealFaceCheckFailure()));
}
void MainWindow::ceshiButton()
{
    interfaceUser::getinstance()->setUsername("535");
    interfaceUser::getinstance()->setPassword("000000");
    this->userLogin();

    ui->accountUserEdit->clear();
    ui->accountPasswordEdit->clear();
    ui->userLabel->show();
}
/*
@brief:处理账号返回信息，msg为登陆成功则跳转到材料提交页。
@param:无
@return:无
@time:2019-10-19
*/
void MainWindow::dealFaceCheckDone ()
{
    loginType ="face";
//    CameraDevice::getinstance ()->quit ();
//    CameraDevice::getinstance ()->wait ();
    this->userLogin();

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
    interfaceUser::getinstance()->setUsername (ui->RegUsername_LineEdit->text());
    interfaceUser::getinstance()->setPassword (ui->RegPwd_LineEdit->text());
    qDebug()<<"uid:"<<interfaceUser::getinstance()->getPassword();
    qDebug()<<"user_info:"<<interfaceUser::getinstance()->getUsername();
    ui->faceRegImageLayout->addWidget(faceReg::getinstance ()->CameraInfo.getviewfinder ());
    faceReg::getinstance ()->CameraInfo.getcamera ()->start();
    faceReg::getinstance ()->moveToThread (faceReg::getinstance ()); //解决类不在一个线程
    faceReg::getinstance ()->start ();
    this->setCurrentIndex(4);
    connect(faceReg::getinstance (),SIGNAL(faceRegSucess()),this,SLOT(dealFaceRegSucess()));
    connect(faceReg::getinstance (),SIGNAL(faceRegFailure()),this,SLOT(dealFaceRegFailure()));
    ui->RegUsername_LineEdit->clear();
    ui->RegPwd_LineEdit->clear();
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
//    QMessageBox::information(this, QString::fromUtf8("注册失败"),QString::fromUtf8("请重新注册"));
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
    ui->userLabel->hide();
    ui->userInfoLabel->clear();
    this->setCurrentIndex(0);
    switch (currentIndex) {
    case 1:
        ui->accountUserEdit->clear();
        ui->accountPasswordEdit->clear();
        break;
    case 2:
        CameraDevice::getinstance ()->quit ();
        CameraDevice::getinstance ()->wait ();
        break;
    case 3:
        ui->RegUsername_LineEdit->clear();
        ui->RegPwd_LineEdit->clear();
        break;
    case 4:
        this->dealFaceRegSucess();
        break;
    case 10:
        QrDecode::getinstance ()->quit();
        QrDecode::getinstance ()->wait();
        break;
    case 9:
        billIndentify->quit();
        billIndentify->wait();
        break;
    default:
        break;
//后续的报销写完之后继续完成清空
    }
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
//        getAllBills();

    } else if (box.clickedButton() == btn2){
        //跳转到扫描报销单页面
        on_postBillButton_clicked();
    }
    this->on_zhichuButton_clicked();
}
/**
 * @brief 获得票据列表
 */
void MainWindow::getAllBills()
{
    //to do
    //获取当前登录人员的所有待处理的单据

    //接入数据

    QList<billInfo> list =interfaceUser::getinstance()->getList();
    int count = list.count();

    mBillList.clear();
    mBillList = list;

    ui->tableWidget->setRowCount(count);
    ui->tableWidget->setColumnCount(5);
    //清空内容但不清空表头
    ui->tableWidget->clearContents();

    for (int i=0; i<count; i++){
        billInfo info = list.at(i);

        QString numberStr = info.billCode;         //单据编号
        QString dateStr = info.billDate;     //日期
        QString accountStr = info.billMoney;
        QString digestStr = info.billUse;           //摘要

        QPushButton *btn = new QPushButton("提交票据");

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(numberStr));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(dateStr));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(accountStr));
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
//    qDebug() << "选择了第" << index << "张票据" ;

    //从单据列表List中找到第index条项目，然后解析获得它的附件列表，接着填入附件列表页
    billInfo info = mBillList.at(index);
    QString strCode = info.billCode;
//    QMessageBox::information(this, "", strCode, QMessageBox::Ok);

    interfaceUser::getinstance()->setBillCode(strCode);
    interfaceUser::getinstance()->getbillAttachment();
    connect(interfaceUser::getinstance(), &interfaceUser::sentDealAttachmentDone, this, &MainWindow::getAttachments);

    ui->stackedWidget->setCurrentIndex(7);
//    getDocumentsListWidget(index);
}
/**
 * @brief 附件列表页实现
 * @param 附件列表
 * @return nothing
 * @time 2019-10-22
 */
void MainWindow::getDocumentsListWidget(int index)
{
}
/**
 * @brief 获得票据附件列表并将它们显示在列表页中
 * @param
 * @return
 * @time 2019-11-10
 */
void MainWindow::getAttachments()
{
    mAttachmentList.clear();
    mAttachmentList = interfaceUser::getinstance()->getAttachment();

    qDebug() << "mAttachmentList的数量为" << mAttachmentList.size();

    ui->billListWidget->clear();

    mAttachmentTypeList.clear();
    //获得mAttachmentTypeList
    mAttachmentTypeList = interfaceUser::getinstance()->getMap();

    for (auto item = mAttachmentTypeList.constBegin(); item != mAttachmentTypeList.constEnd(); item++) {
        QString curType = item.key();       //这是类型key
        QString curTypeStr = item.value();    //这是类型名，写在标签上

        QList<attachment> curList;

        for(int i=0; i<mAttachmentList.size(); i++) {
            attachment info = mAttachmentList.at(i);
            QString strType = info.attachmentType;     //以 F+两位数字 作区分

            if (strType == curType) {
                curList.push_back(info);
            }
        }
        int curCount = curList.size();
        if (curCount > 0) {
            QListWidget *billsList = new QListWidget();
            QSize size = QSize(750, curCount * 110 + 50);
            billsList->setFixedSize(size);

            billsList->addItem(curTypeStr);

            for (int i = 0; i<curCount; i++){
                QListWidgetItem *item1 = new QListWidgetItem();
                item1->setSizeHint(QSize(720, 110));

                attachment attach = curList.at(i);
                QString code = attach.attachmentId;
                QString name = attach.attachmentName;
                QString path = attach.attachmentPath;

                billItem *newItem = new billItem();
                newItem->setIndex(i);

                newItem->setAttachmentType(curType);
                if (curType == "F01") {
                    QString type = attach.invoiceType;
                    QString num = attach.invoiceNumber;
                    newItem->setType(type);
                    newItem->setInvoiceNumber(num);
                }
                newItem->setCode(name);
                newItem->setPath(path);

                connect(newItem, &billItem::startBill, this, &MainWindow::startEmit);
                connect(this, &MainWindow::confirmAttDone, newItem, &billItem::connfirmed);

                billsList->addItem(item1);
                billsList->setItemWidget(item1, newItem);
            }

            QListWidgetItem *item = new QListWidgetItem();
            item->setSizeHint(size);

            ui->billListWidget->addItem(item);
            ui->billListWidget->setItemWidget(item, billsList);
        }

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
//    attType = 0;
    attIndex = index;

    if (mAttachmentList.at(index).attachmentType == "F01") {
        mFapiaoCode = mAttachmentList.at(index).attachmentId;
    } else
        mFapiaoCode = "";
}
/**
 * @brief 票据列表页面提交完成按钮
 * @param 无
 * @return 无
 * @time 2019-10-21
 */
void MainWindow::on_emitFinishBtn_clicked()
{
    QMessageBox::warning(this, "", "请确认是否全部提交？");
    ui->stackedWidget->setCurrentIndex(6);
}
/**
 * @brief 票据列表页面取消按钮
 * @param 无
 * @return 无
 * @time 2019-10-21
 */
void MainWindow::on_emitCancelBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}
/**
 * @brief 开始扫描按钮
 */
void MainWindow::on_scanStartBtn_clicked()
{
    scanPage = new ScanPage;
    scanPage->moveToThread (scanPage); //解决类不在一个线程
    scanPage->start();
    connect(scanPage,SIGNAL(scanDone()),this,SLOT(dealScanDone()));


    //扫描成功并获取发票的信息后，跳转到详情页面
    // to do
    // 将扫描的信息放在发票结构体或类中，在详情页由发票类来获得需要的字段

}
void MainWindow::dealScanDone()
{
    scanPage->quit();
    scanPage->wait();
    this->on_ceShiButton_clicked();
    ui->stackedWidget->setCurrentIndex(9);
    //setBillInfo();        //上面进入扫描，因为会另外开启票据识别的线程，所以不能在这里进行票据的set
}
/**
  *@brief 票据识别后向Mainwindow发送发票信息结构体，这里写入到mFapiaoInfo中
  */
void MainWindow::getBillInfo(QString code, QString money, QString context, QString use)
{
    //再将扫描出来的结构体的内容依次填入
    mFapiaoInfo.billMoney = money;
    mFapiaoInfo.billCode = code;
    mFapiaoInfo.billContext = context;
    mFapiaoInfo.billUse = use;

    //扫描获得了发票数据之后更新页面中的显示
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
    ui->billAccount->setText(mFapiaoInfo.billMoney);       //金额
    ui->billNumber->setText(mFapiaoInfo.billCode);        //发票号
    ui->billContext->setText(mFapiaoInfo.billContext);   //发票内容
    ui->billRemarks->setText(mFapiaoInfo.billUse);   //发票备注

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
    //当要提交的发票号和扫描出来的发票号一致的时候才能正确地跳转回去
    if (mFapiaoCode != "") {
        if (mFapiaoCode == mFapiaoInfo.billCode)
        {
            qDebug() << "比对成功";
            this->setCurrentIndex(7);
            emit confirmAttDone(attIndex);
        }
        else
            QMessageBox::warning(this, "发票号比对不通过", mFapiaoCode + "发票号比对不通过，请重新扫描");
    }
}
/**
 * @brief 发票信息页面：重新扫描按钮
 */
void MainWindow::on_scanAgainBtn_clicked()
{
    //to do
    this->setCurrentIndex(8);
}
/*
@brief:身份证
@param:无
@return:无
@time:2019-10-19
*/
void MainWindow::on_idCardButton_clicked()
{

}

/*
@brief:支出附件
@param:无
@return:无
@time:2019-10-19
*/
void MainWindow::on_zhichuButton_clicked()
{
    interfaceUser::getinstance()->setBillType ("FY");
    interfaceUser::getinstance()->getBillList();
    connect(interfaceUser::getinstance(),SIGNAL(sentDealBillListDone()),this,SLOT(getAllBills()));
}

void MainWindow::on_chaiLvButton_clicked()
{
    interfaceUser::getinstance()->setBillType ("CL");
    interfaceUser::getinstance()->getBillList();
    connect(interfaceUser::getinstance(),SIGNAL(sentDealBillListDone()),this,SLOT(getAllBills()));

}

void MainWindow::on_chuguoButton_clicked()
{
    interfaceUser::getinstance()->setBillType ("CG");
    interfaceUser::getinstance()->getBillList();
    connect(interfaceUser::getinstance(),SIGNAL(sentDealBillListDone()),this,SLOT(getAllBills()));

}

void MainWindow::on_qingkuanButton_clicked()
{
    interfaceUser::getinstance()->setBillType ("QK");
    interfaceUser::getinstance()->getBillList();
    connect(interfaceUser::getinstance(),SIGNAL(sentDealBillListDone()),this,SLOT(getAllBills()));

}

void MainWindow::on_huankuanButton_clicked()
{
    interfaceUser::getinstance()->setBillType ("HK");
    interfaceUser::getinstance()->getBillList();
    connect(interfaceUser::getinstance(),SIGNAL(sentDealBillListDone()),this,SLOT(getAllBills()));

}

void MainWindow::on_neibuButton_clicked()
{
    interfaceUser::getinstance()->setBillType ("ZZ");
    interfaceUser::getinstance()->getBillList();
    connect(interfaceUser::getinstance(),SIGNAL(sentDealBillListDone()),this,SLOT(getAllBills()));

}

void MainWindow::on_lingyongButton_clicked()
{
    interfaceUser::getinstance()->setBillType ("LY");
    interfaceUser::getinstance()->getBillList();
    connect(interfaceUser::getinstance(),SIGNAL(sentDealBillListDone()),this,SLOT(getAllBills()));

}

void MainWindow::on_zhanshouButton_clicked()
{
    interfaceUser::getinstance()->setBillType ("ZS");
    interfaceUser::getinstance()->getBillList();
    connect(interfaceUser::getinstance(),SIGNAL(sentDealBillListDone()),this,SLOT(getAllBills()));

}

void MainWindow::on_postBillButton_clicked()
{
    this->setCurrentIndex(10);
    ui->qrHBoxLayout->addWidget(QrDecode::getinstance()->QrInfo.getviewfinder());
    QrDecode::getinstance ()->QrInfo.getcamera ()->start();
    QrDecode::getinstance ()->moveToThread (QrDecode::getinstance ()); //解决类不在一个线程
    QrDecode::getinstance ()->start ();
    connect(QrDecode::getinstance (),SIGNAL(qrDone(QString)),this,SLOT(dealQrDone(QString)));
}
void MainWindow::dealQrDone(QString billCode)
{
    QrDecode::getinstance ()->quit();
    QrDecode::getinstance()->wait();
    qDebug()<<"dealQrDone槽函数";
    interfaceUser::getinstance()->setBillCode("FY2019120116");
    interfaceUser::getinstance()->getbillAttachment();
    connect(interfaceUser::getinstance(), &interfaceUser::sentDealAttachmentDone, this, &MainWindow::getAttachments);

    this->setCurrentIndex(7);
}

void MainWindow::on_ceShiButton_clicked()
{
    billIndentify = new BillIdentify;
    billIndentify->moveToThread(billIndentify);
    billIndentify->start();
    connect(billIndentify,SIGNAL(success()),this,SLOT(deal_ceShiButton_clicked()));
    connect(billIndentify, &BillIdentify::fapiaoDone, this, &MainWindow::getBillInfo);
}
void MainWindow::deal_ceShiButton_clicked()
{
    billIndentify->quit();
    billIndentify->wait();
}

void MainWindow::on_chatButton_clicked()
{

        qmlRegisterType<Turing>("io.qt.turing", 1, 0, "Turning");

        QQuickView *view = new QQuickView();
        QWidget *widget = QWidget::createWindowContainer(view, this);
        //    connect(turing,&Turing::received,this,&MainWindow::turingSpeak);//turing speak
        view->setSource(QUrl("qrc:/main.qml"));
}

void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->clearContents();
}

void MainWindow::on_scanBackBtn_clicked()
{
    this->setCurrentIndex(7);
}
