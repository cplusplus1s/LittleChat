#pragma once

#include <QMainWindow>
#include <QMap>
#include <QMutex>
#include "ui_ChatWindow.h"
#include "ChatDialog.h"
#include "GlooxManager.h"
#include "UiListener.h"

class ChatWindow : public QMainWindow, public UiListener
{
	Q_OBJECT

public:
	ChatWindow(QWidget *parent = Q_NULLPTR);
	~ChatWindow();

	void initUi();
	void addChatDialog(const QString& id);
	void removeChatDialog(const QString& id);
	int chatDialogCount() const;

signals:
	void newMessage(QString id, QString msg);

public slots:
	void onChatDialogClose(int index);
	void addChatDialogWithMsg(QString id, QString msg);

private:
	virtual void onLogin();
	virtual void onVCardReceived();
	virtual void onItemSubscribed();
	virtual void onItemAdded();
	virtual void onItemRemoved();
	virtual void onItemUpdated();
	virtual void onRosterUpdated();
	virtual void onRosterPresence();
	virtual void onSubscriptionRequest(const std::string& id) {}
	virtual void onMessageReceived(const std::string& msg, const std::string& id);

private:
	Ui::ChatWindow ui;
	GlooxManager *m_networkMng;
	QMap<QString, QDialog*> m_chatDialogs;
	QMutex m_mutex;
};
