#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interfaceuser.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

private:
    Ui::MainWindow *ui;
    int currentIndex; //当前页号
    interfaceUser *InterfaceUser;
};
#endif // MAINWINDOW_H
