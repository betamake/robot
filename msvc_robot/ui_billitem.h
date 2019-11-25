/********************************************************************************
** Form generated from reading UI file 'billitem.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BILLITEM_H
#define UI_BILLITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_billItem
{
public:
    QLabel *label;
    QWidget *widget;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QLabel *label_2;
    QLabel *billNumber;
    QPushButton *billEmitBtn;

    void setupUi(QWidget *billItem)
    {
        if (billItem->objectName().isEmpty())
            billItem->setObjectName(QString::fromUtf8("billItem"));
        billItem->resize(714, 109);
        label = new QLabel(billItem);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 171, 91));
        label->setFrameShape(QFrame::Box);
        widget = new QWidget(billItem);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(180, 10, 111, 80));
        radioButton = new QRadioButton(widget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(10, 10, 119, 20));
        QFont font;
        font.setPointSize(10);
        radioButton->setFont(font);
        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(10, 50, 119, 20));
        radioButton_2->setFont(font);
        label_2 = new QLabel(billItem);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(300, 30, 81, 31));
        QFont font1;
        font1.setPointSize(12);
        label_2->setFont(font1);
        billNumber = new QLabel(billItem);
        billNumber->setObjectName(QString::fromUtf8("billNumber"));
        billNumber->setGeometry(QRect(380, 30, 201, 31));
        billNumber->setFont(font1);
        billEmitBtn = new QPushButton(billItem);
        billEmitBtn->setObjectName(QString::fromUtf8("billEmitBtn"));
        billEmitBtn->setGeometry(QRect(610, 30, 101, 41));
        QFont font2;
        font2.setPointSize(11);
        billEmitBtn->setFont(font2);

        retranslateUi(billItem);

        QMetaObject::connectSlotsByName(billItem);
    } // setupUi

    void retranslateUi(QWidget *billItem)
    {
        billItem->setWindowTitle(QCoreApplication::translate("billItem", "Form", nullptr));
        label->setText(QCoreApplication::translate("billItem", "\345\233\276\347\211\207", nullptr));
        radioButton->setText(QCoreApplication::translate("billItem", "\347\224\265\345\255\220\345\217\221\347\245\250", nullptr));
        radioButton_2->setText(QCoreApplication::translate("billItem", "\347\272\270\350\264\250\345\217\221\347\245\250", nullptr));
        label_2->setText(QCoreApplication::translate("billItem", "\345\217\221\347\245\250\345\217\267\357\274\232", nullptr));
        billNumber->setText(QCoreApplication::translate("billItem", "TextLabel", nullptr));
        billEmitBtn->setText(QCoreApplication::translate("billItem", "\346\217\220\344\272\244\345\217\221\347\245\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class billItem: public Ui_billItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BILLITEM_H
