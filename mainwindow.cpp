#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCurrentIndex(0);
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
    currentIndex = currentIndex;
    ui->stackedWidget->setCurrentIndex(currentIndex);
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
    InterfaceUser = new interfaceUser(this); //用户接口对象
    InterfaceUser->setUsername(username);
    InterfaceUser->setPassword(password);

}
