#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H

#include <QWidget>
/**
 *@brief 日程文件itemView类
 *@time 2019-10-21
 */
namespace Ui {
class scheduleItem;
}

class scheduleItem : public QWidget
{
    Q_OBJECT

public:
    explicit scheduleItem(QWidget *parent = nullptr);
    ~scheduleItem();

    void setTypeAndIndex(int type, int index);

    void setCode(QString strCode);

    void setName(QString name);

signals:
    void startSchedule(int type, int index);

private slots:
    void on_scheduleEmitBtn_clicked();

private:
    Ui::scheduleItem *ui;

    int iType;      //类型，1为日程，2为其他
    int iIndex;     //在对应列表中的序号

    QString mCode;
};

#endif // SCHEDULEITEM_H
