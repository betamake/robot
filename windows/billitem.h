#ifndef BILLITEM_H
#define BILLITEM_H

#include <QWidget>

/*
@brief:发票itemview类
@time:2019-10-21
*/
namespace Ui {
class billItem;
}

class billItem : public QWidget
{
    Q_OBJECT

public:
    explicit billItem(QWidget *parent = nullptr);
    ~billItem();

    void setIndex(int index);

    void setType(QString type);

    void setCode(QString strCode);

signals:
    void startBill(int type, int index);

private slots:
    void on_billEmitBtn_clicked();

private:
    Ui::billItem *ui;

    int iIndex;

    QString type;       //0为纸质发票，1为电子发票

    QString billCode;
};

#endif // BILLITEM_H
