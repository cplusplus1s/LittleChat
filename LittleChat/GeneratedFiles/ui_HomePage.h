/********************************************************************************
** Form generated from reading UI file 'HomePage.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEPAGE_H
#define UI_HOMEPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomePage
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *contactTab;
    QWidget *chattingTab;
    QSplitter *splitter;
    QLabel *profileLabel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *nameLabel;
    QLabel *signLabel;
    QPushButton *addButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *HomePage)
    {
        if (HomePage->objectName().isEmpty())
            HomePage->setObjectName(QStringLiteral("HomePage"));
        HomePage->resize(480, 720);
        centralWidget = new QWidget(HomePage);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 140, 461, 481));
        contactTab = new QWidget();
        contactTab->setObjectName(QStringLiteral("contactTab"));
        tabWidget->addTab(contactTab, QString());
        chattingTab = new QWidget();
        chattingTab->setObjectName(QStringLiteral("chattingTab"));
        tabWidget->addTab(chattingTab, QString());
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(20, 10, 451, 121));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(18);
        profileLabel = new QLabel(splitter);
        profileLabel->setObjectName(QStringLiteral("profileLabel"));
        splitter->addWidget(profileLabel);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        nameLabel = new QLabel(layoutWidget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(nameLabel);

        signLabel = new QLabel(layoutWidget);
        signLabel->setObjectName(QStringLiteral("signLabel"));

        verticalLayout->addWidget(signLabel);

        splitter->addWidget(layoutWidget);
        addButton = new QPushButton(centralWidget);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setGeometry(QRect(10, 630, 31, 31));
        QIcon icon;
        icon.addFile(QStringLiteral(":/LoginWindow/Resources/add_friend.png"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon);
        addButton->setIconSize(QSize(24, 24));
        HomePage->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HomePage);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 480, 18));
        HomePage->setMenuBar(menuBar);
        mainToolBar = new QToolBar(HomePage);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        HomePage->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(HomePage);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        HomePage->setStatusBar(statusBar);

        retranslateUi(HomePage);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(HomePage);
    } // setupUi

    void retranslateUi(QMainWindow *HomePage)
    {
        HomePage->setWindowTitle(QApplication::translate("HomePage", "HomePage", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(contactTab), QApplication::translate("HomePage", "Contacts", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(chattingTab), QApplication::translate("HomePage", "Chatting", nullptr));
        profileLabel->setText(QApplication::translate("HomePage", "Profile", nullptr));
        nameLabel->setText(QApplication::translate("HomePage", "Nickname", nullptr));
        signLabel->setText(QString());
        addButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HomePage: public Ui_HomePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
