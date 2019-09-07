/********************************************************************************
** Form generated from reading UI file 'EmojiWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMOJIWIDGET_H
#define UI_EMOJIWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmojiWidget
{
public:
    QTableWidget *tableWidget;

    void setupUi(QWidget *EmojiWidget)
    {
        if (EmojiWidget->objectName().isEmpty())
            EmojiWidget->setObjectName(QStringLiteral("EmojiWidget"));
        EmojiWidget->resize(82, 77);
        tableWidget = new QTableWidget(EmojiWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 77, 77));
        tableWidget->setRowCount(3);
        tableWidget->setColumnCount(3);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(25);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(25);
        tableWidget->verticalHeader()->setMinimumSectionSize(18);

        retranslateUi(EmojiWidget);

        QMetaObject::connectSlotsByName(EmojiWidget);
    } // setupUi

    void retranslateUi(QWidget *EmojiWidget)
    {
        EmojiWidget->setWindowTitle(QApplication::translate("EmojiWidget", "EmojiWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmojiWidget: public Ui_EmojiWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMOJIWIDGET_H
