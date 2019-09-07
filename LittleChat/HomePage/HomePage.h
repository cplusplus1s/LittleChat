#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QTreeWidget>
#include "ui_HomePage.h"
#include "UiListener.h"
#include "GlooxManager.h"
#include "AddFriendDialog.h"
#include "ChatWindow.h"

const std::string JID_TAIL = "@localopenfire/gloox";

class HomePage : public QMainWindow, public UiListener
{
	Q_OBJECT

public:
	HomePage(QWidget *parent = Q_NULLPTR);
	~HomePage();

	void closeEvent(QCloseEvent *event);

	void initUi();
	void addContact(QString shortId);

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
	void homepageQuit();
	void contactListRefresh();

public slots:
	void on_addButton_clicked();
	void onContactListRefresh();
	void createMucDialog(QTreeWidgetItem *item, int column);

private:
	Ui::HomePage ui;
	QTreeWidget *m_treeWidget;
	GlooxManager *m_networkMng;
	ChatWindow *m_chatWindow;
};
