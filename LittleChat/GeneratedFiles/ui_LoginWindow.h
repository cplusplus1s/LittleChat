/********************************************************************************
** Form generated from reading UI file 'LoginWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindowClass
{
public:
    QWidget *centralWidget;
    QPushButton *loginPushButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *autologinCheckBox;
    QCheckBox *rememberCheckBox;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QComboBox *usernameComboBox;
    QLineEdit *pwLineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LoginWindowClass)
    {
        if (LoginWindowClass->objectName().isEmpty())
            LoginWindowClass->setObjectName(QStringLiteral("LoginWindowClass"));
        LoginWindowClass->resize(600, 400);
        centralWidget = new QWidget(LoginWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        loginPushButton = new QPushButton(centralWidget);
        loginPushButton->setObjectName(QStringLiteral("loginPushButton"));
        loginPushButton->setGeometry(QRect(220, 300, 151, 31));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(160, 240, 291, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        autologinCheckBox = new QCheckBox(layoutWidget);
        autologinCheckBox->setObjectName(QStringLiteral("autologinCheckBox"));

        horizontalLayout->addWidget(autologinCheckBox);

        rememberCheckBox = new QCheckBox(layoutWidget);
        rememberCheckBox->setObjectName(QStringLiteral("rememberCheckBox"));

        horizontalLayout->addWidget(rememberCheckBox);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(160, 140, 291, 81));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        usernameComboBox = new QComboBox(layoutWidget1);
        usernameComboBox->setObjectName(QStringLiteral("usernameComboBox"));

        verticalLayout->addWidget(usernameComboBox);

        pwLineEdit = new QLineEdit(layoutWidget1);
        pwLineEdit->setObjectName(QStringLiteral("pwLineEdit"));

        verticalLayout->addWidget(pwLineEdit);

        LoginWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LoginWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 18));
        LoginWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LoginWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LoginWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LoginWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LoginWindowClass->setStatusBar(statusBar);

        retranslateUi(LoginWindowClass);

        QMetaObject::connectSlotsByName(LoginWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindowClass)
    {
        LoginWindowClass->setWindowTitle(QApplication::translate("LoginWindowClass", "LoginWindow", nullptr));
        loginPushButton->setText(QApplication::translate("LoginWindowClass", "Longin", nullptr));
        autologinCheckBox->setText(QApplication::translate("LoginWindowClass", "AutoLogin", nullptr));
        rememberCheckBox->setText(QApplication::translate("LoginWindowClass", "RememberPassword", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindowClass: public Ui_LoginWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
