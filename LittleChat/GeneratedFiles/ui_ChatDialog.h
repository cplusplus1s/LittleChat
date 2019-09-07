/********************************************************************************
** Form generated from reading UI file 'ChatDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ChatDialog
{
public:
    QTextEdit *outputTextEdit;
    QTextEdit *inputTextEdit;
    QPushButton *emojiButton;

    void setupUi(QDialog *ChatDialog)
    {
        if (ChatDialog->objectName().isEmpty())
            ChatDialog->setObjectName(QStringLiteral("ChatDialog"));
        ChatDialog->resize(400, 300);
        outputTextEdit = new QTextEdit(ChatDialog);
        outputTextEdit->setObjectName(QStringLiteral("outputTextEdit"));
        outputTextEdit->setGeometry(QRect(10, 10, 381, 181));
        outputTextEdit->setReadOnly(true);
        inputTextEdit = new QTextEdit(ChatDialog);
        inputTextEdit->setObjectName(QStringLiteral("inputTextEdit"));
        inputTextEdit->setGeometry(QRect(10, 220, 381, 71));
        emojiButton = new QPushButton(ChatDialog);
        emojiButton->setObjectName(QStringLiteral("emojiButton"));
        emojiButton->setGeometry(QRect(10, 200, 21, 20));
        QIcon icon;
        icon.addFile(QStringLiteral(":/LoginWindow/Resources/emoji.png"), QSize(), QIcon::Normal, QIcon::Off);
        emojiButton->setIcon(icon);

        retranslateUi(ChatDialog);

        QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatDialog)
    {
        ChatDialog->setWindowTitle(QApplication::translate("ChatDialog", "ChatDialog", nullptr));
        emojiButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
