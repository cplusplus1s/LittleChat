#pragma once

#include <QtWidgets/QMainWindow>
#include "inc.h"
#include "ui_LoginWindow.h"
#include "LoginInfoManager.h"
#include "UiListener.h"
#include "GlooxManager.h"
#include "HomePage/HomePage.h"

class LoginWindow : public QMainWindow, public UiListener
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = Q_NULLPTR);

	void InitUi();
	bool SyncDatabase();
	void UpdateDatabase();
	void RefreshCurUserInfo();
	void LoadComboBox();

private:
	virtual void onLogin();
	virtual void onVCardReceived();
	virtual void onItemSubscribed();
	virtual void onItemAdded();
	virtual void onItemRemoved();
	virtual void onItemUpdated();
	virtual void onRosterUpdated();
	virtual void onRosterPresence();
	virtual void onSubscriptionRequest(const std::string& id);
	virtual void onMessageReceived(const std::string& msg, const std::string& id);

signals:
	void switchToHomePage();

private slots:
	void on_usernameComboBox_currentIndexChanged(int index);
	void on_usernameComboBox_editTextChanged(const QString &text);
	void on_autologinCheckBox_stateChanged(int state);
	void on_rememberCheckBox_stateChanged(int state);
	void on_loginPushButton_clicked();

	void onSwitchToHomePage();

private:
	Ui::LoginWindowClass ui;
	QList<LoginInfoManager::UserLoginInfo*> m_loginInfoList;
	int m_curIndex;
	LoginInfoManager *m_databaseMng;
	GlooxManager *m_networkMng;
	HomePage *m_homePage;
};
