/********************************************************************************
** Form generated from reading UI file 'scheduleitem.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULEITEM_H
#define UI_SCHEDULEITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_scheduleItem
{
public:
    QLabel *label;
    QLabel *indexLabel;
    QPushButton *scheduleEmitBtn;
    QLabel *label_2;

    void setupUi(QWidget *scheduleItem)
    {
        if (scheduleItem->objectName().isEmpty())
            scheduleItem->setObjectName(QString::fromUtf8("scheduleItem"));
        scheduleItem->resize(714, 109);
        label = new QLabel(scheduleItem);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 171, 91));
        label->setFrameShape(QFrame::Box);
        indexLabel = new QLabel(scheduleItem);
        indexLabel->setObjectName(QString::fromUtf8("indexLabel"));
        indexLabel->setGeometry(QRect(300, 20, 101, 31));
        QFont font;
        font.setPointSize(12);
        indexLabel->setFont(font);
        scheduleEmitBtn = new QPushButton(scheduleItem);
        scheduleEmitBtn->setObjectName(QString::fromUtf8("scheduleEmitBtn"));
        scheduleEmitBtn->setGeometry(QRect(610, 30, 101, 41));
        QFont font1;
        font1.setPointSize(11);
        scheduleEmitBtn->setFont(font1);
        label_2 = new QLabel(scheduleItem);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 20, 81, 31));
        label_2->setFont(font);

        retranslateUi(scheduleItem);

        QMetaObject::connectSlotsByName(scheduleItem);
    } // setupUi

    void retranslateUi(QWidget *scheduleItem)
    {
        scheduleItem->setWindowTitle(QCoreApplication::translate("scheduleItem", "Form", nullptr));
        label->setText(QCoreApplication::translate("scheduleItem", "\345\233\276\347\211\207", nullptr));
        indexLabel->setText(QCoreApplication::translate("scheduleItem", "1", nullptr));
        scheduleEmitBtn->setText(QCoreApplication::translate("scheduleItem", "\346\217\220\344\272\244\347\245\250\346\215\256", nullptr));
        label_2->setText(QCoreApplication::translate("scheduleItem", "\346\227\245\347\250\213\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class scheduleItem: public Ui_scheduleItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULEITEM_H
