/********************************************************************************
** Form generated from reading UI file 'AddFriendDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIENDDIALOG_H
#define UI_ADDFRIENDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddFriendDialog
{
public:
    QLineEdit *contactIdEdit;
    QLabel *label;
    QPushButton *addButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AddFriendDialog)
    {
        if (AddFriendDialog->objectName().isEmpty())
            AddFriendDialog->setObjectName(QStringLiteral("AddFriendDialog"));
        AddFriendDialog->resize(400, 187);
        contactIdEdit = new QLineEdit(AddFriendDialog);
        contactIdEdit->setObjectName(QStringLiteral("contactIdEdit"));
        contactIdEdit->setGeometry(QRect(130, 50, 241, 20));
        label = new QLabel(AddFriendDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 111, 31));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(10);
        label->setFont(font);
        addButton = new QPushButton(AddFriendDialog);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setGeometry(QRect(200, 120, 71, 31));
        cancelButton = new QPushButton(AddFriendDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(300, 120, 71, 31));

        retranslateUi(AddFriendDialog);

        QMetaObject::connectSlotsByName(AddFriendDialog);
    } // setupUi

    void retranslateUi(QDialog *AddFriendDialog)
    {
        AddFriendDialog->setWindowTitle(QApplication::translate("AddFriendDialog", "AddFriendDialog", nullptr));
        label->setText(QApplication::translate("AddFriendDialog", "ContactID:", nullptr));
        addButton->setText(QApplication::translate("AddFriendDialog", "Add", nullptr));
        cancelButton->setText(QApplication::translate("AddFriendDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddFriendDialog: public Ui_AddFriendDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIENDDIALOG_H
